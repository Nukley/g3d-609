/** @page guidemacosx Setting up a Project in Mac OS X

\htmlonly
<TABLE BORDER=0 WIDTH=80%><TR><TD><I><FONT FACE="Arial">
<A HREF="guidewelcome.html"><IMG SRC="backarrow.gif" BORDER=0 ALIGN=MIDDLE>
Welcome</A></I></FONT></TD><TD ALIGN=RIGHT><FONT FACE="Arial"><I>
<A HREF="guidetutorial.html">
Tutorial <IMG SRC="forwardarrow.gif" BORDER=0 ALIGN=MIDDLE></A></I></FONT></TD></TR></TABLE>
\endhtmlonly


@section introduction Introduction
Setting up %G3D for use with 
<a href="http://www.apple.com/macosx/features/xcode/">Apple Xcode</a>
is rather complicated, mostly due to the weirdnesses of Xcode
and Cocoa development. %G3D applications on OS X must be Cocoa
applications due to the SDL implementation. This document will
walk you through setting up a project. 

@section Prerequisites
These instructions assume that you have some basic familiarity with Xcode. 
These instructions have been designed for OS X 10.4 (Tiger) and Xcode 2.1/2.2. 
Previous versions should of Xcode should work acceptably, though we do not
provide any project files or support for them. Project Builder might work,
but hasn't been tested. Previous versions of Xcode have been used with G3D,
though we are primarily using as up-to-date as possible versions

@section installg3d Installing G3D on Mac OS X
<OL>
<LI>
Download the latest g3d_xxx.zip from <A HREF="http://g3d-cpp.sourceforge.net/#downloads">the sourceforge project page</A>. 
</LI>
<LI>
Unzip the zip file. Put the directory g3d-xxx somewhere nice, such as <CODE>~/src/g3d/</CODE>. 
</LI>
<LI>Install <A HREF="http://libsdl.org">SDL</A> version 1.2.9. 
</LI>
That's it -- the rest of the "install" process is actually getting a project
set up... If you just want to see %G3D in action on the Mac, just open a demo
project's <tt>*.xcodeproj</tt> file and hit, "build and run."
</OL>

@section startingxcode Starting a New Project in Xcode

<OL>
<LI>
<STRONG>Start Xcode.</STRONG>
</LI>
<LI>
<STRONG>Create a New Project</STRONG> - Select File and New Project... In the dialog box
that follows, select Cocoa Application under the heading Application. Pick a name
and location for your new project and select finish. You should now have a window
in Xcode with your new project in it. If you see <I>MY_PROJ</I> anywhere below, assume
that it is actually the name of your new project.
</li>
<LI>
<STRONG>Delete Unused Files</STRONG> - Because Xcode created some files for you, which
you do not need, you will now delete them from your system. Select <tt>main.m</tt> 
and <tt>MainMenu.nib</tt> (hold down command/apple key to multiple select, or do each
one individually). Hit the delete button on your keyboard, or select <I>Delete</I>
from the <I>Edit</I> menu. Xcode will ask you, <I>"The references to be deleted refer
to files on your disk.  Do you wish to delete only the references and not the related
files?"<I> You can go ahead and select <I>"Delete References & Files"</I> because these
will no longer be needed. If it makes you nervous, feel free to just select <I>"Delete
References"</I>.
</LI>
<LI>
<STRONG>Remove Unused Referenced Libraries</STRONG> - Xcode also added some library
references to your project, which are unnecessary. Select <tt>AppKit.framework</tt>, 
<tt>CoreData.framework</tt>, and <tt>Foundation.framework</tt>. Hit the delete button
on your keyboard, or select <I>Delete</I> from the <I>Edit</I> menu. <STRONG>DO NOT
GO ON AUTO PILOT HERE.</STRONG> Xcode will ask you, <I>"The references to be deleted
refer to files on your disk.  Do you wish to delete only the references and not the
related files?"</I> Make sure you select <I>"Delete References"</I>. That should be
the default button.
</LI>
<LI>
Create a new <tt>main.cpp</tt> containing a main() routine, or copy the <tt>main.cpp</tt>
from the <tt>source/demos/</tt> directory to your project's directory, and add the
new or existing file to your Xcode project.
</LI>
<LI>
<STRONG>Add <tt>OpenGL.framework</tt> to your Xcode project.</STRONG> - <tt>OpenGL.framework</tt>
is always located in <tt>/System/Library/Frameworks/</tt>. The dialog for adding the
framework to the project has a checkbox labeled "Copy items into destination group's
folder (if needed)". Make sure that this checkbox is unchecked.
</LI>
<LI>
<STRONG>Add <tt>SDL.framework</tt> to your Xcode project.</STRONG> - <tt>SDL.framework</tt>
should be located in <tt>/Library/Frameworks</tt> or <tt>~/Library/Frameworks</tt>. The
dialog for adding the framework to the project has a checkbox labeled "Copy items into
destination group's folder (if needed)". Make sure that this checkbox is unchecked.
</LI>
<li>
<STRONG>Add the path to the %G3D header files to the include search path.</STRONG> - 
This setting is in the same location as Framework Search Paths. Select the project icon,
press Command-I (or right-click/ctrl-click and "Get Info"), and then modify the "Header
Search Path" entry to include the search path to the %G3D headers.
</LI>
<LI>
<STRONG>Add the %G3D libraries to the project.</STRONG> - Using the Project/Add To Project
menu (or right-click/ctrl-click on "Frameworks" and "Add" - "Existing Frameworks"), add
<tt>libG3D.a</tt> and <tt>libGLG3D.a</tt> to the project. Recent versions of %G3D for
OS X built the Independent JPEG Group (IJG) code into a separate library (<tt>libjpeg.a</tt>).
The IJG code has only recently been folded into <tt>libG3D.a</tt>. If you're using %G3D
6.03 or earlier, you might have to add <tt>libjpeg.a</tt> to your project.
</LI>
<LI><STRONG>Add "-lz" to "Other Linker Flags".</STRONG> -  This tells the linker to
use the system's version of zlib, which G3D requires.
</LI>
<LI>
<STRONG>Very important: Set the link order of libraries.</STRONG> - This is non-obvious
but very important. Failure to set the link order of libraries will give inexplicable
link failures. In the left pane of the Xcode project, select the "Target" item. This will
have at least one item under it corresponding to the name of the application. Select the
application target (it will have a triangle next to it) and expand the triangle by
clicking on it. Under the "Frameworks and Libraries" group make sure that <tt>libG3D.a</tt>
and <tt>libGLG3D.a</tt> are listed before <tt>OpenGL.framework</tt>. Failure to do this
will result in over 80 link errors related to OpenGL extensions. 
</LI>
<LI>
<STRONG>Add <tt>SDLMain.m</tt> and <tt>SDLMain.h.</tt></STRONG> - SDL for OS X requires
that we build <tt>SDLMain.m</tt> into the project. Failure to do this will result in the
symbol <tt>_main</tt> being undefined when you try to link your %G3D application.
<tt>SDLMain.m</tt> and <tt>SDLMain.h</tt> are included in %G3D for OS X for convenience.
Note that they are not part of %G3D per se, and they are part of the SDL distribution.
</LI>
<LI>
<STRONG>Write Your Code!</STRONG> -  You can now write code for %G3D just like you would
for Linux or Windows.
</LI>
<LI><STRONG>Optional: Nullify Windows Cludges.</STRONG> - Define <tt>__stdcall</tt> and
<tt>__cdecl</tt> to evaluate to nothing in the preprocessor: <tt>__stdcall</tt> and
<tt>__cdecl</tt> are needed for Windows code, but they don't do anything on OS X. You can
add <tt>__stdcall=</tt> and <tt>__cdecl=</tt> to the "Preprocessor Macros" section of
the Project Info.
</LI>
<LI><STRONG>Optional: Set Relative Paths.</STRONG> -  In general when working in Xcode,
make sure all source files have Path Type "Relative to Enclosing Group" or "Relative to
Project" selected in file info (rather than "Absolute Path"). This is so that if the
Xcode project is moved or a directory name is changed, the project file links will not
break. If you highlight all source and header files and press Cmd-I, you can set Path
Type easily.
</LI>
</OL>

Caveats for G3D on OS X:

<UL>

<LI>
There is a version of SDL available through Fink, the popular open-source package
manager for OS X.  We have no idea if the fink version of SDL for OS X will work with
G3D.  This document assumes that you're using the SDL library for OS X that is
downloaded from <tt>http://www.libsdl.org/</tt> or one of its mirrors. We suspect that
the version of SDL for OS X available from fink uses X11, which is wholly different
from the windowing and rendering system that G3D for OS X assumes.
</LI>
<LI>
You can also use the command line tool 'xcodebuild' to build the G3D libraries from
the Xcode project files, but without using the Xcode IDE. You can see an example of how
this is done for <tt>G3DTest</tt> in <tt>G3DOSX/make-osx-dev.sh</tt>.
</LI>
</UL>


**/
