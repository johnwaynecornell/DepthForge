# DepthForge
Stereographic depth editor.

DepthForge is a depth editor for Stereography, it currently outputs Anaglyph(red/cyan) which may be seen with standard
(red/cyan) '3d' glasses and Quad buffer support ie NVIDIA Quadro/3dvision for full color stereographic emersion.

I decided to release it under the GNU GPL (general public license) to support the developing art of Stereography. You are
free to do most things except take credit for my work. Please read this license before downloading the source or compiling.
Read https://www.gnu.org/licenses/gpl-3.0.en.html before proceeding.

The principle of operation is an algorithm I call 2.5d. It works by storing a Z value for every pixel in the image. This Z
represents depth. I decided to use 32bit float for the Z component (although it is possible to impliment the algorithm in 
integer formats as well, ie a byte would give 256 levels of depth). When its time to render the two halfs(left/right) of the
stereographic image, these Z values control the offset from the original image to the half being rendered, in a linear manner
(proportional to the width of the original image). Once the new locations of 2 pixels, adjacant in a line, are known, there 
color and depth values are interpolated between over these new locations (utilizing a depth buffer to show the closer pixel 
when their is overlap).

The application itself is used by accepting a brush from the top left of the edit window. This brush can then be draged accross
the image (pulling with the left mouse button and pushing with the right) moving the image under the brush closer or further.
There are currently 4 brushes to chose from with different charachteristics.

Create and Enjoy!

Please e-mail any corespondance to john.wayne.cornell@gmail.com
