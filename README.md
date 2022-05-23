# CPP-Playing-Card-Detector



<h2><b>1. Overview </b></p></h2>

Project in C++ with only STL. This program finds, marks and recognizes playing cards not using an extra image processing library such as OpenCV. This program calculates the perimeter and area of playing cards, determines their center and marks suits inside them.  The program finds playing cards based on the 'flood filling' algorithm, which assumes that a certain set of points is given starter (grains, seeds), from which the growth of areas begins. 


An example photo showing the operation of the program is presented below.
<img width="550" height="350" src = img/ideal.jpg/>



Pictures showing the operation of the program are presented below
<img width="550" height="350" src = img/findcont.jpg/>
<img width="520" height="750" src = img/console.jpg/>

<hr>

<h2><b>2. Working principle </b></p></h2>


The most important functions in this program are:
- grayscale function <br/>
The purpose of this function is to convert an original image to grayscale. Making an image in shades of gray is such a transformation image to get for each image pixel according to the brightness of a pixel such a share of each of these components alone. For this purpose, an image pixel is first read of a specific color with an appropriate share of each of the basic components and extracts the R, G, B components. Then the brightness of each color is summed basic and divides this sum completely by 3. After this operation, a synthesis should be made
color from these three components. The operations are performed in a loop for each image pixel.
The photo below shows the original image after conversion.
<img width="550" height="350" src = img/gray.jpg/>
<br><br>


- binarization function <br/>
The purpose of this function is to separate the foreground objects from the background. It designates for the image brightness threshold, and then pixels brighter than the threshold set are given one value, and the darker ones another. In this program, this function assigns an intensity value 1 pixels whose intensity is greater than 0.45 and assigns a value of 0 to others.
The photo below shows the original image after applying the thresholding
<img width="550" height="350" src = img/bin.jpg/>


- findCard function <br/>
The purpose of this function is to find,fill and circle playing cards. The feature of finding cards is based on the 'flood filling' algorithm, which assumes that a certain set of points is given starter (seeds), from which the growth of areas begins. Given attachment point
it is up to grain if it meets the uniformity test, so all pixels are consistent in eight directions to the start pixel and having the same color as it will be colored in
new fill color. It follows that the area must be filled before the operation
solid color. On the other hand, adjacent areas may have any colors, but different from
the color of the filled area. The pixel we start filling the area with (grain
fill) must be inside the area to be filled. If the grain hits the
'Fertile ground', it fills it with color and tries to further propagate in eight directions.
This way the entire area will be painted over with the specified color. Thanks to the use of
of this algorithm, the cards may be objects defined by rectangles. <br/>
Source: www.eduinf.waw.pl/inf/utils/002_roz/2008_08.php

The image after the application of the flood algorithm is presented below.
<img width="550" height="350" src = img/floodfill.jpg/>


The picture below shows  the original image with the playing cards circled in rectangles.
<img width="550" height="350" src = img/floodfill_rec.jpg/>
<hr>


- colorBorder function <br/>
This function fills the area between the rectangle's edges and the outline playing
cards in order to search each symbol in a specific area. After this function is used in the analyzed rectangle, only the card suits are black.
The picture below shows the original image after applying this function
<img width="550" height="350" src = img/colorborder.jpg/>
<hr>



- findSign function <br/>
The purpose of this function is to find and mark suits on each card. Finding suits do the same as finding cards, only an algorithm
works inside each rectangle. As in these rectangles only the suits are black
the algorithm searches for black elements and fills them with white. This feature uses
method of removing unnecessary elements - microsuits (microsymbols) and card values. Method
it works by calculating the diameter of all suits on the card and their averages
standard deviation. If the difference between the maximal element is a suit,
which has the largest diameter and the diameter of the test piece is greater than the deviation
standard, such an element is removed. The picture below is presented after applying the algorithm to search for black elements and fill them with white on the 7 of hearts card
<img width="550" height="350" src = img/findsign.jpg/>

The picture below shows the image of suits and removing unnecessary elements on the 7 of hearts card
<img width="550" height="350" src = img/findsign2.jpg/>

<hr>

- findCont function <br/>
This function finds and marks the outlines of playing cards, determines the coordinates of the center and counts the perimeter of the playing cards. To find the outline of a card, the color of the card and the color of the suits on it must be
different from the fill color of the analyzed rectangle. The algorithm works like this that
starting from the coordinates being the geometrical center of the rectangle it moves
along the coordinates on the radius and if it hits a fill color value
(colorBorder) then colors the border of the card to the value = 0.99 and saves these coordinates
as those on the outskirts of the card. The card circumference is calculated by adding up the next ones
distances between successive coordinates located on the outskirts of the card. Center
card is determined with the getD2 function, which calculates the mean standard deviation
in the set of distances of the established "suspect" point as the center, and the constituting points
edge of the card. The center of the card will be when this standard deviation will be the smallest.
Thus, if in the vicinity of the point "suspected" of the center (surroundings = eight coherence
specified by matrix ofst) there is no point for which this value of getD2 was
smaller, this point is the center of the card. And if there is a point in the vicinity of this point which
is better (i.e. has a smaller standard deviation), the algorithm goes in its direction.
The action ends when there is no better point in the eight coherent environment.
<hr>


- setSymArr function<br/>
The effect of this function are 4 matrices storing histograms for patterns -
a histogram of the distance between the point being the geometric center of the rectangle
encompassing the symbol (suits), and the subsequent points on the edges of the symbol pattern. For building
function getFFT_ is responsible for such a histogram. Four symbol patterns needed
for card identification are presented in the picture below.
<img width="450" height="350" src = img/suits_patterns.jpg/>


- getFFT_ function<br/>
Its task is to create a distance function (along the radius) of the symbol shape from the center
the rectangle that includes the symbol. The idea behind this function is that for a specific symbol
in the rectangle, the pointer is set to the center resulting from the diagonal
and searches for points on the radius until white is encountered. If white is encountered then
this radius (distance from center to edges) is recorded. It creates this distance function
for symbol patterns and for all symbols on the card.