/** @page license License

\htmlonly
<TABLE BORDER=0 WIDTH=80%><TR><TD><I><FONT FACE="Arial">
<A HREF="guideintro.html"><IMG SRC="backarrow.gif" BORDER=0 ALIGN=MIDDLE>
Introduction</A></I></FONT></TD><TD ALIGN=RIGHT><FONT FACE="Arial"><I>
<A HREF="guideinstall.html">
Installation <IMG SRC="forwardarrow.gif" BORDER=0 ALIGN=MIDDLE></A></I></FONT></TD></TR></TABLE>
\endhtmlonly

@section intent Intent of License
   (This section is informal and not legally binding.)

   <BR> This library is free code-- you can use it without charge and
   it is minimally legally encumbered.  Unlike some other free libraries,
   we <u>do not</u> require you to release
   your source code or make your own program open source.

   <P> I intend the license (below) to protect me and the other
   contributors from liability and allow you to use the source however
   you want.  You can make your own closed or open-source programs,
   sell them, give them away, whatever.

   <P>
   You have an obligation to say "this software is based in part on
   the work of the Independent JPEG Group" in your documentation or
   application help if you use the G3D::GImage class because it is based on
   the IJG library.  The OpenGL headers and ZLib headers included may
   be freely distributed provided their copyright notices remain
   intact. 

   <P>
   For convenience, G3D::license is a function that returns the license
   string you must put in your documentation.  G3D::GApp will automatically
   write a file (g3d-license.txt) to disk with the contents of this
   license unless you tell it not to.
   
   <P>
   Most of the data resources have either entered the public domain and have
   been in several published papers or are data that I have explicitly 
   received permission to distribute with G3D.  The G3D fonts are actually font
   images, not TrueType font descriptions and may be freely
   distributed.  As a rule of thumb, you can freely use and distribute
   anything you find in the data directory but may need permission to use
   it in a commercial product.  Check the various copyright.txt files
   in the data directories for specific information.

   <P> 

   You are required by the BSD license to acknowledge G3D in your 
   documentation.  This can be as minimal as a note buried in the
   fine print at the end of a manual or a text file accompanying
   your program.  I appreciate it if you acknowledged the library
   more publicly but you aren't required to.

   <P>
   
   Likewise, you are encouraged but not required to submit patches to
   improve the library for the benefit of all.  E-mail me with bugs,
   patches, and questions.  <P>

   -Morgan McGuire
   &lt;<I><A HREF="mailto:matrix@graphics3d.com">matrix@graphics3d.com</A></I>&gt;
    
   <HR>

  @section reallicense License

   <I>G3D is licensed under the <A HREF="http://www.opensource.org/licenses/bsd-license.php">BSD license</A>, 
   with portions controlled by the <A HREF="IJG-README.TXT">IJG license</A> and 
   <A HREF="libpng-LICENSE.txt">PNG Reference Library license</A></I>

  <CODE>
   <IMG SRC="http://opensource.org/trademarks/osi-certified/web/osi-certified-120x100.gif">
   <DT>This product uses software from the G3D project (http://g3d-cpp.sf.net)
   <DT>Copyright &copy; 2000-2006, Morgan McGuire
   <DT>All rights reserved.
   <P>
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   <P>
   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
   <P>
   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
   <P>
   Neither the name of Morgan McGuire, Williams College, Brown University, nor the names of
   its contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   <P>
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
   THE POSSIBILITY OF SUCH DAMAGE.
  </CODE>

   <P>
      You must also agree to be bound by the terms of the Independent JPEG
      Group license for the portions of this library that are based
      on the work of the Independent JPEG Group, <B>if you use those
      portions</B>.  Note: if you do not use the G3D::GImage class,
      this clause does not apply to you because the linker will
      strip that code from your project.  The <A
      HREF="IJG-README.TXT">IJG-README.TXT</A> file contains the
      Independent JPEG Group license.

   </OL>

 */