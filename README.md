# CPP-Playing-Card-Detector


### Overview
Project in C++ with only STL. This program finds, marks and recognizes playing cards not using an extra image processing library such as OpenCV. This program also calculates the perimeter of playing cards, determines their center and marks suits inside them.  The program finds playing cards based on the **flood fill** algorithm, which assumes that a certain set of points is given starter (grains, seeds), from which the expansion of areas begins. 


The example photo showing the operation of this program is presented below.
<img width="550" height="350" src = img/ideal.jpg/>


The images below show how this program works.
<img width="550" height="350" src = img/findcont.jpg/>
<img width="520" height="750" src = img/console.jpg/>


### Working principle 
The most important functions of the program are described in the sections below.
- <b>grayscale function </b> <br/> </b>
The purpose of this function is to convert an original photo to grayscale. A grayscale image is an image in which the proportion of each R, G, B component is the same. Making an image in grayscale comes down to such transformation of the image to obtain for each pixel of the image, according to the degree of brightness of the pixel, the same share of each of these components. For this purpose, first, a pixel of the image with a specific color is read with the appropriate share of each of the basic components and the R, G, B components are extracted. Then, the brightness of each color is summed up and divides this sum without remainder by 3. After this operation, it performs synthesis color from these three components. The operations are performed in a loop for each image pixel.
The image below shows the original photo after conversion.
<img width="550" height="350" src = img/gray.jpg/>
<br><br>


- <b>binarization function </b> <br/>
The purpose of this function is to separate the foreground objects from the background. 
It designates for brightness threshold, and then pixels brighter than the threshold are given one value and the darker one the other. In this program, this function assigns an intensity value 1 to pixels whose intensity is greater than 0.45, and assigns a value of 0 to others.
The image below shows the grayscale image after applying the thresholding.
<img width="550" height="350" src = img/bin.jpg/>


- <b> findCard function </b> <br/>
The purpose of this function is to find, fill and circle playing cards. The card finder feature is based
on the ‘flood fill’ algorithm, which assumes that a certain set of points is given starting points (seeds), from which the growth of areas begins. A given connection point is grainy if it satisfies the uniformity test, so all pixels coherent in eight directions to the starting pixel and having the same color as it will be colored to new fill color. It follows that the filled area must have before the operation uniform color. Contiguous areas, however, can have any color, but different from the color of the filled area. The pixel from which we start filling the area (grain fill) must be inside the fill area. If the seed hits
fertile ground, it fills it with color and tries to propagate further in eight directions.
This way, the entire area will be painted with the specified color. Thanks to the application
cards of this algorithm can be objects defined by rectangles.. <br/>
Source (in Polish): www.eduinf.waw.pl/inf/utils/002_roz/2008_08.php 
The image after the application of the flood fill algorithm is presented below.
<img width="550" height="350" src = img/floodfill.jpg/>


The picture below shows  the original image with the playing cards circled in rectangles.
<img width="550" height="350" src = img/floodfill_rec.jpg/>



- <b> colorBorder function </b> <br/>
This function is designed to fill the area between the edges of the rectangle and the contour
cards to search for individual symbols in a specific area. After using this function, only card symbols are black in the analyzed rectangle.
The picture below shows the original image after applying this and previous functions.

<img width="550" height="350" src = img/colorborder.jpg/>



- <b>findSign function </b> <br/>
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


- <b> findCont function </b> <br/>
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


- <b> setSymArr function </b> <br/>
The effect of this function are 4 matrices storing histograms for patterns -
a histogram of the distance between the point being the geometric center of the rectangle
encompassing the symbol (suits), and the subsequent points on the edges of the symbol pattern. For building
function getFFT_ is responsible for such a histogram. Four symbol patterns needed
for card identification are presented in the picture below.
<img width="450" height="350" src = img/suits_patterns.jpg/>


- <b> getFFT_ function </b> <br/>
Its task is to create a distance function (along the radius) of the symbol shape from the center
the rectangle that includes the symbol. The idea behind this function is that for a specific symbol
in the rectangle, the pointer is set to the center resulting from the diagonal
and searches for points on the radius until white is encountered. If white is encountered then
this radius (distance from center to edges) is recorded. It creates this distance function
for symbol patterns and for all symbols on the card.