#ifndef card_H
#define card_H
#include <math.h>
#define M_PI  (3.14159265)
#define HIST_VO_    (  256)			 // number of items in the histogram
#define HIST_VOL    ( 1024)			 // number of distances (radius) from the center to the edges of the rectangle
								 

class card {
   public:
        card* prev;		// prev and next point to card objects
        card* next;
        int cardValue;			// the card values [2, 7, 8, 9]
        int cardColor;			// the card colors [0, 1, 2, 3]
        int color;			// the card color 0, 1 [red, black]
        unsigned int inCard;		// indicator Id of 'Mothers' card	
        unsigned int Id;  		// for subobjects (symbols) inCard matches the ID of the card
        unsigned int blX, blY, trX, trY;
        double oO, aR, xC, yC;		// oO = perimeter, aR = area, xC, yC = card center coordinates
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

