# CPP Playing Card Detector


### Overview
Project in C++ with only STL. This program finds, marks and recognizes playing cards not using an extra image processing library such as OpenCV. This program also calculates the perimeter of playing cards, determines their center and marks suits inside them.  The program finds playing cards based on the **flood fill** algorithm, which assumes that a certain set of points is given starting points  (grains, seeds), from which the growth of areas begins.


The example photo showing the operation of this program is presented below.
<img width="550" height="350" src = img/ideal.jpg/>


The images below show how this program works.
<img width="550" height="350" src = img/findcont.jpg/>
<img width="520" height="750" src = img/console.jpg/>
<br>

### Working principle 
The most important functions of the program are described in the sections below.
- <b>grayscale function </b> <br/> </b>
The purpose of this function is to convert an original photo to grayscale. A grayscale image is an image in which the proportion of each R, G, B component is the same. Making an image in grayscale comes down to such transformation of the image to obtain for each pixel of the image, according to the degree of brightness of the pixel, the same share of each of these components. For this purpose, first, a pixel of the image with a specific color is read with the appropriate share of each of the basic components and the R, G, B components are extracted. Then, the brightness of each color is summed up and divides this sum without remainder by 3. After this operation, it performs synthesis color from these three components. The operations are performed in a loop for each image pixel.
The image below shows the original photo after conversion.
<img width="550" height="350" src = img/gray.jpg/>
<br>


- <b>binarization function </b> <br/>
The purpose of this function is to separate the foreground objects from the background. 
It designates for brightness threshold, and then pixels brighter than the threshold are given one value and the darker one the other. In this program, this function assigns an intensity value 1 to pixels whose intensity is greater than 0.45, and assigns a value of 0 to others.
The image below shows the grayscale image after applying the thresholding.
<img width="550" height="350" src = img/bin.jpg/>
<br>

- <b> findCard function </b> <br/>
The purpose of this function is to find, fill and circle playing cards. The card finder feature is based
on the ‘flood fill’ algorithm, which assumes that a certain set of points is given starting points (seeds), from which the growth of areas begins. A given connection point is grainy if it satisfies the uniformity test, so all pixels coherent in eight directions to the starting pixel and having the same color as it will be colored to new fill color. It follows that the filled area must have before the operation uniform color. Contiguous areas, however, can have any color, but different from the color of the filled area. The pixel from which we start filling the area (grain fill) must be inside the fill area. If the seed hits
fertile ground, it fills it with color and tries to propagate further in eight directions.
This way, the entire area will be painted with the specified color. Thanks to the application
cards of this algorithm can be objects defined by rectangles. <br/>
Source (in Polish): www.eduinf.waw.pl/inf/utils/002_roz/2008_08.php <br/> 
The image after the application of the flood fill algorithm is presented below.
<img width="550" height="350" src = img/floodfill.jpg/>
<br>

The picture below shows  the original image with the playing cards circled in rectangles.
<img width="550" height="350" src = img/floodfill_rec.jpg/>
<br>


- <b> colorBorder function </b> <br/>
This function is designed to fill the area between the edges of the rectangle and the contour
cards to search for individual symbols in a specific area. After using this function, only card symbols are black in the analyzed rectangle.
The picture below shows the original image after applying this and previous functions.

<img width="550" height="350" src = img/colorborder.jpg/>
<br>


- <b>findSign function </b> <br/>
The purpose of this function is to find and mark symbols on individual cards.
Finding symbols is done in the same way as finding cards, just an algorithm
works inside each rectangle. As in these rectangles only symbols are black
the algorithm searches for black elements and fills them with white. This function uses
a method of removing redundant elements - color microsymbols and card values. Method
This one works by calculating the diameter of all the symbols on the card and their averages
standard deviation. If the difference between the maximal element - symbol,
which has the largest diameter and the diameter of the test piece is greater than the deviation
standard, such an element is removed. The image after applying the algorithm that searches for black elements and filling them with white
suit on the 7 of hearts card is shown below.
<img width="550" height="350" src = img/findsign.jpg/>

The picture below shows the image of suits and removing unnecessary elements on the 7 of hearts card
<img width="550" height="350" src = img/findsign2.jpg/>


- <b> findCont function </b> <br/>
This function finds and marks card contours, determines the coordinates of the center and calculates the perimeter
cards. In order to find the outline of a card, the color of the card and the color of the symbols on it must be
different from the fill color in the rectangle being analyzed. The algorithm works like this
starting from the coordinates that are the geometric center of the rectangle, it moves
along the radius coordinates and if it hits a fill color value
(colorBorder) it colors the edges of the card to the value colCon= 0.99 and saves these coordinates
as those on the edges of the card. Calculation of the circumference of the card consists in adding up the successive ones
distances between successive coordinates located on the edges of the card. Middle
is determined using the getD2 function, which calculates the mean standard deviation
in the set of distances of a fixed "suspect" point as the center, and the points constituting
the edge of the card. The center of the card will be when this standard deviation is the smallest.
Therefore, if in the vicinity of a point "suspicious" of the center (environment = octagonal
specified by the ofst matrix) there is no point where this getD2 function value was
less then this point is the center of the card. And if there is a point in the vicinity of this point, which
is better (i.e. has a smaller standard deviation), the algorithm goes in that direction.
The operation ends if there is no better point in the octagonal neighborhood.


- <b> setSymArr function </b> <br/>
The effect of this function is 4 matrices storing histograms for patterns -
histogram of the distance between the point being the geometric center of the rectangle
enclosing the symbol, and successive points on the edges of the symbol pattern. For building
getFFT_ function is responsible for such a histogram. Patterns of four symbols needed
to identify the cards are shown in the picture below.
<img width="450" height="350" src = img/suits_patterns.jpg/>
<br>

- <b> getFFT_ function </b> <br/>
Its task is to create a distance function (along the radii) of the symbol shape from the center
rectangle that contains the symbol. The idea behind this function is that for a specific symbol
within the rectangle, the pointer is set to the center of the diagonal
and the points on the radius are searched until white is found. If white is encountered, this ray is there
recorded (distance from center to edges). This distance function creates
for symbol patterns and for all symbols in the card.