# thepainter

Written and tested on Ubuntu 22.04.

Simulates painting with oil. Input is a photograph. Output is (hopefully) a painterly rendering.

I have combined elements from two academic papers to create my own Stroke-Based Rendering (SBR) software. I used "Painterly Rendering with Curved Brush Strokes of Multiple Sizes" by Aaron Hertzmann for the general framework but I didn't particularly like his curved brush strokes. I prefer straight strokes with an oil paint texture. So, I turned to "An Algorithm For Automatic Painterly Rendering Based On Local Source Image Approximation" by Michio Shiraishi and Yasushi Yamaguchi to handle the brush strokes.

To create the executable, compile the code in directory "thepainter" using "make -f Makefile_g/Makefile_O" and then go into the "main" directory and create the exec using "make".

Test cases are given in the "test" directory.

Info about thepainter (theory behind it and how to use it) can be found here:

[Non Photorealistic Rendering Software - The Painter](https://3dstereophoto.blogspot.com/2018/07/non-photorealistic-rendering-software.html)

[Non Photorealistic Rendering - Stroke-Based Rendering (SBR)](https://3dstereophoto.blogspot.com/2018/05/non-photorealistic-rendering-stroke.html)

Dependencies (check the Makefiles):

"common" repo
