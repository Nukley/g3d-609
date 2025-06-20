/** @page errorfaq Error FAQ


There are a few confusing error messages you can run into when compiling,
linking, and debugging programs that use G3D.  Here are the common fixes.
<BR>
<BR>
<I>Most linker errors are caused by linking against the wrong version of the G3D libraries.<BR>
VC6 needs the "win32-lib" directory, VC7.1 uses the "win32-lib-7" directory.<BR>
The VC8 libraries must currently be built from CVS by the end user. ("win32-lib-8" directory).</I>
<P>



<P><B>MSVCPRT.LIB(MSVCP60.dll) : error LNK2005: "public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::assign(class s
td::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &,unsigned int,unsigned int)" (?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z) already defined in xxx(yyy)</B>
<P>
G3D changes the linker settings for files, so you should generally #include <G3DAll.h> or #include<graphics3d.h> before any other includes and use it in every source (or header) file.  Also, include all of G3D and not just the specific class you are using.

<P><B><CODE>Error C2440: 'delete' : cannot convert from 'class G3D::ReferenceCountedPointer<class G3D::GFont>' to '' No user-defined-conversion operator available that can perform this conversion, or the operator cannot be called</CODE></B>
<P>
You called <CODE>delete</CODE> on a reference counted class.  You do not need to delete G3D::GFontRef, G3D::TextureRef or any other Ref class; just
set them to NULL when you don't need them and the underlying memory will be recovered.

<P><B>../include\G3D/ReferenceCount.h(159) : error C2664: 'setPointer' : cannot convert parameter 1 from 'class G3D::Shader *' to 'class SphereMap *'
        Types pointed to are unrelated; conversion requires reinterpret_cast, C-style cast or function-style cast
        D:\games\cpp\source\Debug\main.cpp(167) : see reference to function template instantiation '__thiscall G3D::ReferenceCountedPointer<class SphereMap>::G3D::ReferenceCountedPointer<class SphereMap>(const class G3D::ReferenceCountedPointer<clas
s G3D::Shader> &)' being compiled</B><P>

You tried to assign a reference counted pointer from the wrong type
(e.g. TextureRef a = GFontRef::create().

<P><B>error C2440: 'return' : cannot convert from 'class A *' to 'class B *'
Types pointed to are unrelated; conversion requires reinterpret_cast, C-style cast or function-style cast
d:\games\cpp\source\include\g3d\referencecount.h(194) : see reference to function template instantiation 'class B *__cdecl G3D::ReferenceCountedPointer<class B>::safecast(class A *)' being compiled</B>
<P>
You tried to assign a reference counted pointer from the wrong type
(e.g. TextureRef a = GFontRef::create().

<P><B>Program "randomly" crashes AMD systems</B><P>
See the
<A HREF="http://support.microsoft.com/default.aspx?scid=http://support.microsoft.com:80/support/kb/articles/Q270/7/15.ASP&NoWebContent=1">Microsoft Knowledge Base article</A>.

<P><B>undefined symbol SDL_main</B><P>
The linking error: <CODE>undefined symbol SDL_main </CODE> can result from a main() function that doesn't have argc
and argv arguments.  For example:
<CODE> int main() {..}</CODE>

is no good...  make sure you have

<CODE> int main(int argc, char **argv) {..} </CODE>

<P><B>Application Error: The application failed to initialize properly (0xc0000022). Click on OK to terminate the application.</B><P>

   At runtime, your program can't load the SDL.dll, zlib.dll, or glut32.dll dynamic libraries.

   This is probably occurring because the current working directory is invalid or because
   the files and directory exist but cannot be accessed.  This frequently occurs when a Windows
   program is running from a Linux file system via Samba.  Make sure you have set the e<B>X</B>ecute

   bit on the DLL's from Linux.
   <P>

<B><CODE>../include/G3D/g3dmath.h:27: limits: No such file or directory</CODE></B>

<BR>You are using an old version of GCC on Linux. Add these lines to your .cshrc:<br>
<PRE>
   setenv CC gcc-3.2
   setenv CXX g++-3.2
</PRE>

<P><B><CODE>
msvcprtd.lib(MSVCP60D.dll) : error LNK2005: "public: __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::~basic_string<char,struct std::char_traits<char>,class std::allocator<char> >(void)" (??1?$basic_strin
g@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ) already defined in main.obj

...

MSVCRTD.lib(MSVCRTD.dll) : error LNK2005: _strncpy already defined in LIBCD.lib(strncpy.obj)
MSVCRTD.lib(MSVCRTD.dll) : error LNK2005: __isctype already defined in LIBCD.lib(isctype.obj)
LINK : warning LNK4098: defaultlib "MSVCRTD" conflicts with use of other libs; use /NODEFAULTLIB:library
Debug/GLG3D_Demo.exe : fatal error LNK1169: one or more multiply defined symbols found
</CODE></B>

   <P>
   You are linking against the wrong standard library.  Navigate the MSVC menus to
   Project:Settings:C++:Code Generation and select
   "Debug Multithreaded DLL" for your debug build and "Multithreaded DLL" for
   your release build.
   <P>

<P>
<B><CODE>array.h(233) : error C2512: : no appropriate default constructor available
   array.h(195) : while compiling class-template member function 'void __thiscall G3D::Array<class X>::resize(int,bool)'</CODE></B>

<P> You created a G3D::Array of a class that does not provide a default
constructor (constructor with no arguments).  Define a default constructor
for your class-- G3D::Array needs it to initialize new elements when you
invoke G3D::Array::resize().

<P><B><CODE>sdlmain.lib(SDL_main.obj) : error LNK2005: _main already defined in main.obj</CODE></B>
<BR>You need to <CODE>\#include &lt;SDL.h&gt;</CODE> in your main.cpp file.

<P>
<B><CODE>error LNK2001: unresolved external symbol _glActiveTextureARB</CODE></B>
<BR>Some other (e.g. MSVC .NET) program's include directory is listed before the
G3D directory and contains conflicting OpenGL drivers.  Reorder the include directories
under Tools/Options/Directories

<P>

<B><CODE>fatal error C1083: Cannot open include file: 'G3DAll.h': No such file or directory</CODE></B>
<BR> You need to add the g3d/include directory to your include path.

<B>LINK : fatal error LNK1181: cannot open input file
   "glg3d.lib"</B> <BR> You need to add the graphics3d/lib directory
   to your library path (instructions above)

<P><B>"warning LNK4229: invalid directive" in MSVC build</B><P>
When linking against G3D's libraries the following linker errors are produced
<CODE>G3D-debug.lib(TextInput.obj) : warning LNK4229: invalid directive '/alternatename:__imp_??$?9DU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@PBD@Z=__imp_??9std@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@PBD@Z' encountered; ignored
G3D-debug.lib(TextInput.obj) : warning LNK4229: invalid directive '/alternatename:__imp_??$?8DU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@PBD@Z=__imp_??8std@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@PBD@Z' encountered; ignored
G3D-debug.lib(TextInput.obj) : warning LNK4229: invalid directive '/alternatename:__imp_??$?8DU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@0@Z=__imp_??8std@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@0@Z' encountered; ignored
</CODE>
etc...

Odds are you're linking against the wrong version of the libraries. Current G3D distributions include two versions of windows libraries. For MSVC version 6, the libraries reside in win32-lib, and for version 7.0 (MSVC dot net) win32-lib7. Note there are TWO MSVC "dot net" versions, 7.0 (2002) and 7.1 (2003). They are incompatible with each other. If you have the latest 7.1 version, or any more recent version (such as the free Visual C++ 2005 Express Beta) you will need to build the libraries on your own.

<P><B>G3D-debug.lib(jutils.obj) : fatal error LNK1202: "vc60.pdb" is missing debugging information for referencing module</B><P>
That means you are using a build that was created with debugging info, but you don't have the program database (pdb) that was built with it.  The most common cause is using G3D on a different machine than the one on which you compiled G3D.
<P>
There are three solutions:<P>
1. Build G3D on your local machine<P>
2. Build G3D without debug info (Project:Settings:C++:Debug Info)<P>
3. Use an official G3D build, since they are created without debug info.


<P><B>My G3D based project will not build with Visual Studio 2005<BR>
or<BR>
Error linking:<BR>
error LNK2001: unresolved external symbol "__declspec(dllimport) public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::iterator __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::end(void)"
</B><P>

G3D 6.07 and below does not include library files that link with Visual Studio 2005 (VC++ 8 runtime), as VS2005 was not available at the time of G3D release.
This problem will be solved with the upcoming release of G3D 6.08.
Until then, the recommended solution is to checkout the CVS source of G3D, open the solution in VS2005 and convert the project. Then build the libraries. This will build the library files with VC++ 8, which can then be used with a VS2005 based project.

<P><B>/usr/lib/gcc-lib/i586-suse-linux/3.3.5/../../../../i586-suse-linux/bin/ld: Warning: type of symbol `glGenerateMipmapEXT' changed from 2 to 1 in /t/3rdParty/g3d-6_07/linux-lib/libGLG3D_debug.a(libGLG3D_debug_a-glcalls.o)<BR>
And<BR>
/t/3rdParty/g3d-6_07/linux-lib/libGLG3D_debug.a(libGLG3D_debug_a-Texture.o)(.text+0x18e): In function `dimensionToTarget':
../../../source/GLG3Dcpp/Texture.cpp:82: undefined reference to `G3D::_internal::_releaseInputGrab_()'
</B><P>

The source is being linked in the wrong order for the dependencies.
To fix this, link GLG3D, G3D and then GL in that order.
A sample compile command would look like:<BR>
	g++ -L<DIRECTORY> -o<OUTPUT>./main.o -lGLG3D_debug -ljpeg -lSDL -lpng -lG3D_debug -lGL -lGLU


*/
