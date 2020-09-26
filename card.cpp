#include "card.h"
#include <math.h>

// initializing the 'card' object is associated with resetting pointers
card::card(){
    prev = 0;
    next = 0;
}

card::~card(){
    ;
}

// gives the card diameter
unsigned int card::getRad(){
    unsigned int W = trX - blX;		// diagonal length
    unsigned int H = trY - blY;
    return (unsigned int )floor(pow((float)W * (float)W + (float)H * (float)H, 0.5));
}


