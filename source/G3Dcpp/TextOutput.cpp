/**
  @file TextOutput.cpp

  @maintainer Morgan McGuire, morgan@graphics3d.com
  @created 2004-06-21
  @edited  2004-10-21

  Copyright 2000-2004, Morgan McGuire.
  All rights reserved.
 */

#include "G3D/TextOutput.h"
#include "G3D/Log.h"
#include "G3D/fileutils.h"

namespace G3D {

TextOutput::TextOutput(const TextOutput::Options& opt) {
    setOptions(opt);
    filename = "";
    setIndentLevel(0);
    startingNewLine = true;
    currentColumn = 0;
    inDQuote = false;
}


TextOutput::TextOutput(const std::string& fil, const TextOutput::Options& opt) {
    setOptions(opt);
    filename = fil;
    setIndentLevel(0);
    startingNewLine = true;
    currentColumn = 0;
    inDQuote = false;
}


void TextOutput::setIndentLevel(int i) {
    indentLevel = i;

    // If there were more pops than pushes, don't let that take us below 0 indent.
    // Don't ever indent more than the number of columns.
    indentSpaces = 
        iClamp(option.spacesPerIndent * indentLevel, 
               0, 
               option.numColumns - 1);
}


void TextOutput::setOptions(const Options& _opt) {
    option = _opt;

    debugAssert(option.numColumns > 1);

    setIndentLevel(indentLevel);

    newline = (option.newlineStyle == Options::NEWLINE_WINDOWS) ? "\r\n" : "\n";
}


void TextOutput::pushIndent() {
    setIndentLevel(indentLevel + 1);
}


void TextOutput::popIndent() {
    setIndentLevel(indentLevel - 1);
}


static std::string escape(const std::string& string) {
    std::string result = "";

    for (std::string::size_type i = 0; i < string.length(); ++i) {
        char c = string.at(i);
        switch (c) {
        case '\0':
            result += "\\0";
            break;

        case '\r':
            result += "\\r";
            break;

        case '\n':
            result += "\\n";
            break;

        case '\t':
            result += "\\t";
            break;

        case '\\':
            result += "\\\\";
            break;

        default:
            result += c;
        }
    }

    return result;
}

void TextOutput::writeString(const std::string& string) {
    // Convert special characters to escape sequences
    this->printf("\"%s\"", escape(string).c_str());
}


void TextOutput::writeNumber(double n) {
    this->printf("%f ", n);
}


void TextOutput::writeNumber(int n) {
    this->printf("%d ", n);
}


void TextOutput::writeSymbol(const std::string& string) {
    if (string.size() > 0) {
        // TODO: check for legal symbols?
        this->printf("%s ", string.c_str());
    }
}

void TextOutput::writeSymbols(
    const std::string& a,
    const std::string& b,
    const std::string& c,
    const std::string& d,
    const std::string& e,
    const std::string& f) {

    writeSymbol(a);
    writeSymbol(b);
    writeSymbol(c);
    writeSymbol(d);
    writeSymbol(e);
    writeSymbol(f);
}


void TextOutput::printf(const std::string formatString, ...) {
    va_list argList;
    va_start(argList, formatString);
    this->vprintf(formatString.c_str(), argList);
    va_end(argList);
}


void TextOutput::printf(const char* formatString, ...) {
    va_list argList;
    va_start(argList, formatString);
    this->vprintf(formatString, argList);
    va_end(argList);
}


void TextOutput::convertNewlines(const std::string& in, std::string& out) {
    // TODO: can be significantly optimized in cases where
    // single characters are copied in order by walking through
    // the array and copying substrings as needed.

    if (option.convertNewlines) {
        out = "";
        for (uint32 i = 0; i < in.size(); ++i) {
            if (in[i] == '\n') {
                // Unix newline
                out += newline;
            } else if ((in[i] == '\r') && (i + 1 < in.size()) && (in[i + 1] == '\n')) {
                // Windows newline
                out += newline;
                ++i;
            } else {
                out += in[i];
            }
        }
    } else {
        out = in;
    }
}


void TextOutput::writeNewline() {
    for (uint32 i = 0; i < newline.size(); ++i) {
        indentAppend(newline[i]);
    }
}


void TextOutput::writeNewlines(int numLines) {
    for (int i = 0; i < numLines; ++i) {
        writeNewline();
    }
}


void TextOutput::wordWrapIndentAppend(const std::string& str) {
    // TODO: keep track of the last space character we saw so we don't
    // have to always search.

    if ((option.wordWrap == Options::WRAP_NONE) ||
        (currentColumn + (int)str.size() <= option.numColumns)) {
        // No word-wrapping is needed

        // Add one character at a time.
        // TODO: optimize for strings without newlines to add multiple
        // characters.
        for (uint32 i = 0; i < str.size(); ++i) {
            indentAppend(str[i]);
        }
        return;
    }

    // Number of columns to wrap against
    int cols = option.numColumns - indentSpaces;
    
    // Copy forward until we exceed the column size, 
    // and then back up and try to insert newlines as needed.
    for (uint32 i = 0; i < str.size(); ++i) {

        indentAppend(str[i]);
        if ((str[i] == '\r') && (i + 1 < str.size()) && (str[i + 1] == '\n')) {
            // \r\n, we need to hit the \n to enter word wrapping.
            ++i;
            indentAppend(str[i]);
        }

        if (currentColumn >= cols) {
            debugAssertM(str[i] != '\n' && str[i] != '\r',
                "Should never enter word-wrapping on a newline character");            

            // True when we're allowed to treat a space as a space.
            bool unquotedSpace = option.allowWordWrapInsideDoubleQuotes || ! inDQuote;

            // Cases:
            //
            // 1. Currently in a series of spaces that ends with a newline
            //     strip all spaces and let the newline
            //     flow through.
            //
            // 2. Currently in a series of spaces that does not end with a newline
            //     strip all spaces and replace them with single newline
            //
            // 3. Not in a series of spaces
            //     search backwards for a space, then execute case 2.

            // Index of most recent space
            uint32 lastSpace = data.size() - 1;

            // How far back we had to look for a space
            uint32 k = 0;
            uint32 maxLookBackward = currentColumn - indentSpaces;

            // Search backwards (from current character), looking for a space.
            while ((k < maxLookBackward) &&
                (lastSpace > 0) &&
                (! ((data[lastSpace] == ' ') && unquotedSpace))) {
                --lastSpace;
                ++k;

                if ((data[lastSpace] == '\"') && !option.allowWordWrapInsideDoubleQuotes) {
                    unquotedSpace = ! unquotedSpace;
                }
            }

            if (k == maxLookBackward) {
                // We couldn't find a series of spaces

                if (option.wordWrap == Options::WRAP_ALWAYS) {
                    // Strip the last character we wrote, force a newline,
                    // and replace the last character;
                    data.pop();
                    writeNewline();
                    indentAppend(str[i]);
                } else {
                    // Must be Options::WRAP_WITHOUT_BREAKING
                    //
                    // Don't write the newline; we'll come back to
                    // the word wrap code after writing another character
                }
            } else {
                // We found a series of spaces.  If they continue 
                // to the new string, strip spaces off both.  Otherwise
                // strip spaces from data only and insert a newline.                

                // Find the start of the spaces.  firstSpace is the index of the
                // first non-space, looking backwards from lastSpace.
                uint32 firstSpace = lastSpace;
                while ((k < maxLookBackward) &&
                    (firstSpace > 0) &&
                    (data[firstSpace] == ' ')) {
                    --firstSpace;
                    ++k;
                }

                if (k == maxLookBackward) {
                    ++firstSpace;
                }

                if (lastSpace == (uint32)data.size() - 1) {
                    // Spaces continued up to the new string
                    data.resize(firstSpace + 1);
                    writeNewline();

                    // Delete the spaces from the new string
                    while ((i < str.size() - 1) && (str[i + 1] == ' ')) {
                        ++i;
                    }
                } else {
                    // Spaces were somewhere in the middle of the old string.
                    // replace them with a newline.

                    // Copy over the characters that should be saved
                    Array<char> temp;
                    for (uint32 j = lastSpace + 1; j < (uint32)data.size(); ++j) {
                        char c = data[j];

                        if (c == '\"') {
                            // Undo changes to quoting (they will be re-done
                            // when we paste these characters back on).
                            inDQuote = !inDQuote;
                        }
                        temp.append(c);
                    }

                    // Remove those characters and replace with a newline.
                    data.resize(firstSpace + 1);
                    writeNewline();

                    // Write them back
                    for (uint32 j = 0; j < (uint32)temp.size(); ++j) {
                        indentAppend(temp[j]);
                    }

                    // We are now free to continue adding from the
                    // new string, which may or may not begin with spaces.

                } // if spaces included new string
            } // if hit indent
        } // if line exceeded
    } // iterate over str
}


void TextOutput::indentAppend(char c) {

    if (startingNewLine) {
        for (int j = 0; j < indentSpaces; ++j) {
            data.push(' ');
        }
        startingNewLine = false;
        currentColumn = indentSpaces;
    }

    data.push(c);

    // Don't increment the column count on return character
    // newline is taken care of below.
    if (c != '\r') {
        ++currentColumn;
    }
    
    if (c == '\"') {
        inDQuote = ! inDQuote;
    }

    startingNewLine = (c == '\n');
    if (startingNewLine) {
        currentColumn = 0;
    }
}


void TextOutput::vprintf(const char* formatString, va_list argPtr) {
    std::string str = vformat(formatString, argPtr);

    std::string clean;
    convertNewlines(str, clean);
    wordWrapIndentAppend(clean);
}


void TextOutput::commit(bool flush) {
    FILE* f = fopen(filename.c_str(), "wb");
    fwrite(data.getCArray(), 1, data.size(), f);
    if (flush) {
        fflush(f);
    }
    fclose(f);
}


void TextOutput::commitString(std::string& out) {
    // Null terminate
    data.push('\0');
    out = data.getCArray();
    data.pop();
}


std::string TextOutput::commitString() {
    std::string str;
    commitString(str);
    return str;
}



/////////////////////////////////////////////////////////////////////

void serialize(const float& b, TextOutput& to) {
    to.writeNumber(b);
}


void serialize(const bool& b, TextOutput& to) {
    to.writeSymbol(b ? "true" : "false");
}


void serialize(const int& b, TextOutput& to) {
    to.writeNumber(b);
}


void serialize(const uint8& b, TextOutput& to) {
    to.writeNumber(b);
}


void serialize(const double& b, TextOutput& to) {
    to.writeNumber(b);
}


}
