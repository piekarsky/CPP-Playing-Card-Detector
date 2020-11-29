#include "card.h"
#include <math.h>

/*
this function initializes the 'card' object which is associated with resetting pointers
*/ 
card::card(){
    prev = 0;
    next = 0;
}

card::~card(){
    ;
}

/*
this function gives the card diameter
*/
unsigned int card::getRad(){
    unsigned int W = trX - blX;		// diagonal length
    unsigned int H = trY - blY;
    return (unsigned int )floor(pow((float)W * (float)W + (float)H * (float)H, 0.5));
}

bool list::next(){
    bool re = true;
    if(acT != 0){
        acT = acT->next;	// if this current element exists then set pointer to whichever is next

        re = acT != 0;		 // if not zero then there is a successor, and if not it was the last card
    } else { 
        re = false;		     // false is when act is zero
    }
    return re;
}


bool list::empty(){
    return (toP == 0);		 // top is zero when the list is empty
}

void list::get(unsigned int &blX, unsigned int &blY, unsigned int &trX, unsigned int &trY, unsigned int &Id){
    blX     = acT->blX;
    blY     = acT->blY;
    trX     = acT->trX;
    trY     = acT->trY;
    Id      = acT->Id;
}



