#ifndef card_H
#define card_H
#include <math.h>
#define M_PI  (3.14159265)
#define HIST_VO_    (  256)			 // the number of items in the histogram
#define HIST_VOL    ( 1024)			 // the number of distances (radius) from the center to the edges of the rectangle
								 

class card {
	public:
		card* prev;				// previous and next point to card objects
        	card* next;
        	int cardValue;				// the card values [e.g. 2, 5, 7, 8, 10]
        	int cardColor;				// the card suits [0, 1, 2, 3]
        	int color;				// the card colors [0 = red, 1 = black]
        	unsigned int idCard;			// Id of the 'Mother' card	
        	unsigned int Id;  			
        	unsigned int blX, blY, trX, trY;
        	double oO, aR, xC, yC;			// oO = perimeter, aR = area, xC, yC = card center coordinates
        	double ffT[HIST_VO_];
        	card();
        	virtual ~card();
        	unsigned int getRad();
		int xc, yc;
       		int getArr();		

   	protected:
    	private:
};

#endif 

