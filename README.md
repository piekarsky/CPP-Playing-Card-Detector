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


- binarization function
The purpose of this function is to separate the foreground objects from the background. It designates for
the image brightness threshold, and then pixels brighter than the threshold set are given one
value, and the darker ones another. In this program, this function assigns an intensity value
1 pixels whose intensity is greater than 0.45 and assigns a value of 0 to others.