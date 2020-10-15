# Playing-Card-Detection-without-using-OpenCV

This program finds and recognizes playing cards not using an extra image processing library such as OpenCV. The program also calculates circuit of playing cards and determine the geometric center of cards. The program finds playing cards based on the 'flood filling' algorithm, which assumes that a certain set of points is given starter (grains, seeds), from which the growth of areas begins. 

The most important functions in this program are:
- Grayscale function <br/>
The purpose of this function is to convert an original image to grayscale. Making an image in shades of gray is such a transformation image to get for each image pixel according to the brightness of a pixel such a share of each of these components alone. For this purpose, an image pixel is first read of a specific color with an appropriate share of each of the basic components and extracts the R, G, B components. Then the brightness of each color is summed basic and divides this sum completely by 3. After this operation, a synthesis should be made
color from these three components. The operations are performed in a loop for each image pixel.
The photo below shows an original image after conversion.


- binarization function <br/>
The purpose of this function is to separate the foreground objects from the background. It designates for the image brightness threshold, and then pixels brighter than the threshold set are given one value, and the darker ones another. In this program, this function assigns an intensity value 1 pixels whose intensity is greater than 0.45 and assigns a value of 0 to others.

- findCard function <br/>
The purpose of this function is to find and circle playing cards. The feature of finding cards is based on the 'flood filling' algorithm, which assumes that a certain set of points is given starter (grains, seeds), from which the growth of areas begins. Given attachment point
it is up to grain if it meets the uniformity test, so all pixels are consistent in eight directions to the start pixel and having the same color as it will be colored in
new fill color. It follows that the area must be filled before the operation
solid color. On the other hand, adjacent areas may have any colors, but different from
the color of the filled area. The pixel we start filling the area with (grain
fill) must be inside the area to be filled. If the grain hits the
'Fertile ground', it fills it with color and tries to further propagate in eight directions.
This way the entire area will be painted over with the specified color. Thanks to the use of
of this algorithm, the cards may be objects defined by rectangles.
Source: www.eduinf.waw.pl/inf/utils/002_roz/2008_08.php
