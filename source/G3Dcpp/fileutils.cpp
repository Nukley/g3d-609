/**
 @file fileutils.cpp
 
 @author Morgan McGuire, graphics3d.com
 
 @author  2002-06-06
 @edited  2005-02-24
 */

#include "G3D/platform.h"
#include "G3D/fileutils.h"
#include "G3D/BinaryInput.h"
#include "G3D/g3dmath.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "G3D/stringutils.h"

#ifdef G3D_WIN32
   // Needed for _getcwd
   #include <direct.h>
   #include <io.h>
#else
   #include <dirent.h>
   #include <fnmatch.h>
   #include <unistd.h>
   #define _getcwd getcwd
#endif
#include <stdio.h>
#include "G3D/BinaryOutput.h"

/**
 Pick up libjpeg headers locally on Windows, but from the system on all other platforms.
*/
extern "C" {
#if (defined(_MSC_VER) || defined(__MINGW32__))
	#include "../IJG/jpeglib.h"
#else
	#include <jpeglib.h>
#endif
}

#ifdef G3D_WIN32
    //for _mkdir and _stat
    #include <direct.h>
#else
    #define _stat stat
#endif


namespace G3D {
    
    namespace _internal {
        Array<std::string> currentFilesUsed(0);
    }


std::string resolveFilename(const std::string& filename) {
    if (filename.size() >= 1) {
        if ((filename[0] == '/') || (filename[0] == '\\')) {
            // Already resolved
            return filename;
        } else {

            #ifdef G3D_WIN32
                if ((filename.size() >= 2) && (filename[1] == ':')) {
                    // There is a drive spec on the front.
                    if ((filename.size() >= 3) && ((filename[2] == '\\') || 
                                                   (filename[2] == '/'))) {
                        // Already fully qualified
                        return filename;
                    } else {
                        // The drive spec is relative to the
                        // working directory on that drive.
                        debugAssertM(false, "Files of the form d:path are"
                                     " not supported (use a fully qualified"
                                     " name).");
                        return filename;
                    }
                }
            #endif
        }
    }

    char buffer[1024];

    // Prepend the working directory.
    _getcwd(buffer, 1024);

    return format("%s/%s", buffer, filename.c_str());
}


std::string readFileAsString(
    const std::string& filename) {

    _internal::currentFilesUsed.append(filename);

    int64 length = fileLength(filename);

    if (length == -1) {
        return "";
    }

    char* buffer = (char*)malloc(length + 1);
    debugAssert(buffer);
    FILE* f = fopen(filename.c_str(), "rb");
    debugAssert(f);
    int ret = fread(buffer, 1, length, f);
	debugAssert(ret == length);(void)ret;
    fclose(f);

    buffer[length] = '\0';
    std::string s = std::string(buffer);
    free(buffer);

    return s;
}


int64 fileLength(const std::string& filename) {
    struct _stat st;
    int result = _stat(filename.c_str(), &st);
    
    if (result == -1) {
        return -1;
    }

    return st.st_size;
}


FILE* createTempFile() {
    // Added to the G3D version of jpeglib
#ifdef _MSC_VER
    return _robustTmpfile();
#else
    return tmpfile();
#endif
}

///////////////////////////////////////////////////////////////////////////////

void writeStringToFile(
    const std::string&          str,
    const std::string&          filename,
    bool                        flush) {

    // Make sure the directory exists.
    std::string root, base, ext, path;
    Array<std::string> pathArray;
    parseFilename(filename, root, pathArray, base, ext); 

    path = root + stringJoin(pathArray, '/');
    if (! fileExists(path)) {
        createDirectory(path);
    }

    FILE* file = fopen(filename.c_str(), "wb");

    debugAssert(file);

    fwrite(str.c_str(), str.size(), 1, file);

    if (flush) {
        fflush(file);
    }
    fclose(file);
}

///////////////////////////////////////////////////////////////////////////////

/**
 Creates the directory (which may optionally end in a /)
 and any parents needed to reach it.
 */
void createDirectory(
    const std::string&  dir) {
    
	if (dir == "") {
		return;
	}

    std::string d;

    // Add a trailing / if there isn't one.
    switch (dir[dir.size() - 1]) {
    case '/':
    case '\\':
        d = dir;
        break;

    default:
        d = dir + "/";
    }

    // If it already exists, do nothing
    if (fileExists(d.substr(0, d.size() - 1))) {
        return;
    }

    // Parse the name apart
    std::string root, base, ext;
    Array<std::string> path;

    std::string lead;
    parseFilename(d, root, path, base, ext);
    debugAssert(base == "");
    debugAssert(ext == "");

    // Begin with an extra period so "c:\" becomes "c:\.\" after
    // appending a path and "c:" becomes "c:.\", not root: "c:\"
    std::string p = root + ".";

    // Create any intermediate that doesn't exist
    for (int i = 0; i < path.size(); ++i) {
        p += "/" + path[i];
        if (! fileExists(p)) {
	    // Windows only requires one argument to mkdir,
	    // where as unix also requires the permissions.
	    #ifndef G3D_WIN32
	 	 mkdir(p.c_str(),0777);
 	    #else
                 _mkdir(p.c_str());
	    #endif
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

bool fileExists(
    const std::string& filename) {

	if (filename == "") {
		return true;
	}

    struct _stat st;
    return _stat(filename.c_str(), &st) != -1;
}

///////////////////////////////////////////////////////////////////////////////

void copyFile(
    const std::string&          source,
    const std::string&          dest) {

    #ifdef G3D_WIN32
        CopyFile(source.c_str(), dest.c_str(), FALSE);
    #else
        // TODO: don't use BinaryInput and BinaryOutput
        // Read it all in, then dump it out
        BinaryInput  in(source, G3D_LITTLE_ENDIAN);
        BinaryOutput out(dest, G3D_LITTLE_ENDIAN);
        out.writeBytes(in.getCArray(), in.size());
        out.commit(false);
    #endif
}

//////////////////////////////////////////////////////////////////////////////

void parseFilename(
    const std::string&  filename,
    std::string&        root,
    Array<std::string>& path,
    std::string&        base,
    std::string&        ext) {

    std::string f = filename;

    root = "";
    path.clear();
    base = "";
    ext = "";

    if (f == "") {
        // Empty filename
        return;
    }

    // See if there is a root/drive spec.
    if ((f.size() >= 2) && (f[1] == ':')) {
        
        if ((f.size() > 2) && isSlash(f[2])) {
        
            // e.g.  c:\foo
            root = f.substr(0, 3);
            f = f.substr(3, f.size() - 3);
        
        } else {
        
            // e.g.  c:foo
            root = f.substr(2);
            f = f.substr(2, f.size() - 2);

        }

    } else if ((f.size() >= 2) & isSlash(f[0]) && isSlash(f[1])) {
        
        // e.g. //foo
        root = f.substr(0, 2);
        f = f.substr(2, f.size() - 2);

    } else if (isSlash(f[0])) {
        
        root = f.substr(0, 1);
        f = f.substr(1, f.size() - 1);

    }

    // Pull the extension off
    {
        // Find the period
        size_t i = f.rfind('.');

        // Make sure it is before a slash!
        size_t j = iMax(f.rfind('/'), f.rfind('\\'));
        if ((i != std::string::npos) && (i > j)) {
            ext = f.substr(i + 1, f.size() - i - 1);
            f = f.substr(0, i);
        }
    }

    // Pull the basename off
    {
        // Find the last slash
        size_t i = iMax(f.rfind('/'), f.rfind('\\'));
        
        if (i == std::string::npos) {
            
            // There is no slash; the basename is the whole thing
            base = f;
            f    = "";

        } else if ((i != std::string::npos) && (i < f.size() - 1)) {
            
            base = f.substr(i + 1, f.size() - i - 1);
            f    = f.substr(0, i);

        }
    }

    // Parse what remains into path.
    size_t prev, cur = 0;

    while (cur < f.size()) {
        prev = cur;
        
        // Allow either slash
        size_t i = f.find('/', prev + 1);
        size_t j = f.find('\\', prev + 1);
        if (i == std::string::npos) {
            i = f.size();
        }

        if (j == std::string::npos) {
            j = f.size();
        }

        cur = iMin(i, j);

        if (cur == std::string::npos) {
            cur = f.size();
        }

        path.append(f.substr(prev, cur - prev));
        ++cur;
    }
}



/**
 Helper for getFileList and getDirectoryList.

 @param wantFiles       If false, returns the directories, otherwise
                        returns the files.
 @param includePath     If true, the names include paths
 */
static void getFileOrDirList(
	const std::string&		filespec,
	Array<std::string>&		files,
	bool					wantFiles,
	bool					includePath) {

	bool test = wantFiles ? true : false;

	std::string path = "";

    // Find the place where the path ends and the file-spec begins
    size_t i = filespec.rfind('/');
    size_t j = filespec.rfind('\\');
    
    // Drive letters on Windows can separate a path
    size_t k = filespec.rfind(':');
    
    if ((j != std::string::npos) && (j > i) ||
        (i == std::string::npos)) {
        i = j;
    }
    
    if ((k != std::string::npos) && (k > i) ||
        (i == std::string::npos)) {
        i = k;
    }
    
    // If there is a path, pull it off
    if (i != std::string::npos) {
        path = filespec.substr(0, i + 1);
    }
   
    std::string prefix = path;

    if (path.size() > 0) {
        // Strip the trailing character
        path = path.substr(0, path.size() - 1);
    }

    #ifdef G3D_WIN32
	    struct _finddata_t fileinfo;

        long handle = _findfirst(filespec.c_str(), &fileinfo);
        int result = handle;

        while (result != -1) {
            if ((((fileinfo.attrib & _A_SUBDIR) == 0) == test) && 
                strcmp(fileinfo.name, ".") &&
                strcmp(fileinfo.name, "..")) {
                
                if (includePath) {
                    files.append(prefix + fileinfo.name);
                } else {
                    files.append(fileinfo.name);
                }
            }
            
            result = _findnext(handle, &fileinfo);
        }
    #else
        // Linux implementation
        DIR* dir = opendir(path.c_str());

        if (dir != NULL) {
            struct dirent* entry = readdir(dir);

            while (entry != NULL) {

                // Exclude '.' and '..'
                if (strcmp(entry->d_name, ".") &&
                    strcmp(entry->d_name, "..")) {
                    
                    // Form a name with a path
                    std::string filename = prefix + entry->d_name;
                    
                    // See if this is a file or a directory
                    struct _stat st;
                    bool exists = _stat(filename.c_str(), &st) != -1;

                    if (exists &&

                        // Make sure it has the correct type
                        (((st.st_mode & S_IFDIR) == 0) == test) &&

                        // Make sure it matches the wildcard
                        (fnmatch(filespec.c_str(),
                                 filename.c_str(),
                                 FNM_PATHNAME) == 0)) {
                        
                        if (includePath) {
                            files.append(filename);
                        } else {
                            files.append(entry->d_name);
                        }
                    }
                }

                entry = readdir(dir);
            }
        }
        closedir(dir);

    #endif
}


void getFiles(
	const std::string&			filespec,
	Array<std::string>&			files,
	bool						includePath) {

	getFileOrDirList(filespec, files, true, includePath);
}


void getDirs(
	const std::string&			filespec,
	Array<std::string>&			files,
	bool						includePath) {

	getFileOrDirList(filespec, files, false, includePath);
}


std::string filenameBaseExt(const std::string& filename) {
    int i = filename.rfind("/");
    int j = filename.rfind("\\");

    if ((j > i) && (j >= 0)) {
        i = j;
    }

#   ifdef G3D_WIN32
        j = filename.rfind(":");
        if ((i == -1) && (j >= 0)) {
            i = j;
        }
#   endif

    if (i == -1) {
        return filename;
    } else {
        return filename.substr(i + 1, filename.length() - i);
    }
}


std::string filenameExt(const std::string& filename) {
    int i = filename.rfind(".");
    if (i >= 0) {
        return filename.substr(i + 1, filename.length() - i);
    } else {
        return "";
    }
}


std::string filenamePath(const std::string& filename) {
    int i = filename.rfind("/");
    int j = filename.rfind("\\");

    if ((j > i) && (j >= 0)) {
        i = j;
    }

#   ifdef G3D_WIN32
        j = filename.rfind(":");
        if ((i == -1) && (j >= 0)) {
            i = j;
        }
#   endif

    if (i == -1) {
        return "";
    } else {
        return filename.substr(0, i+1);
    }
}


bool isDirectory(const std::string& filename) {
    struct _stat st;
    bool exists = _stat(filename.c_str(), &st) != -1;
    return exists && ((st.st_mode & S_IFDIR) != 0);
}


bool filenameContainsWildcards(const std::string& filename) {
    return (filename.find('*') != std::string::npos) || (filename.find('?') != std::string::npos);
}


bool fileIsNewer(const std::string& src, const std::string& dst) {
    struct _stat sts;
    bool sexists = _stat(src.c_str(), &sts) != -1;

    struct _stat dts;
    bool dexists = _stat(dst.c_str(), &dts) != -1;

    return sexists && ((! dexists) || (sts.st_mtime > dts.st_mtime));
}


Array<std::string> filesUsed() {
    return _internal::currentFilesUsed;
}

}

#ifndef G3D_WIN32
  #undef _stat
#endif
