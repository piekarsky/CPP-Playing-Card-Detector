# Playing-Card-Detection-without-using-OpenCV

The program finds and makes a circle the cards, as well as calculates the perimeters of the cards and determine the geometric center of the card. The program finds cards based on the 'flood filling' algorithm, which assumes that a certain set of points is given starter (grains, seeds), from which the growth of areas begins. 

The most important functions in the program are:
- Grayscale function
The purpose of this function is to convert the original (color) image to scale
gray. Making an image in shades of gray comes down to such a transformation
image to get for each image pixel according to the brightness of the pixel such
the share of each of these components alone. For this purpose, the image pixel is first read
of a specific color with an appropriate share of each of the basic components
and extracts the R, G, B components. Then the brightness of each color is summed up
basic and divides this sum completely by 3. After this operation, a synthesis should be made
color from these three components. The operations are performed in a loop for each image pixel.
The photo below shows the perfect image after conversion.