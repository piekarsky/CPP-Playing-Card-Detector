#include "list.h"
#include <math.h>
#include <iostream>



list::list(){
    toP = 0;
    boT = 0;
    acT = 0;
    Id = 0;
    stepHST = 1.0 / (double)HIST_VO_;
}


list::~list(){
    ;
}



void list::push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inCard){
	
	// push - inserts a new element (bottomleft, topright and inCard)
	
	card* cardA = new card();		 	 // initialize a new 'card' object
    if(toP == 0)toP = karta;
    Id++;					                   // inkrement the id
    karta->blX = blX;
    karta->blY = blY;
    karta->trX = trX;
    karta->trY = trY;
    karta->next = boT;				  // card next = bot because it sets the pointer to the beginning
    karta->Id   = Id;
    karta->inKarta  = inCard;
    if(karta->next != 0)karta->next->prev = karta;
    karta->prev  = 0;
    karta->karta = 0;
    boT = karta; 
    acT = karta;					  // index to the created object tab
    for(unsigned int i = 0; i < HIST_VO_; i++){
        karta->ffT[i] = 0.0;				  // reset this matrix to add items to the histogram
    }
}
bool list::top(){ 
    bool re = true;;
    if(boT != 0){
        acT = toP;
    } else {
        re = false;			// the list is empty
    }
    return re;
}
bool list::bot(){
    bool re = true;
    if(boT != 0){
        acT = boT;
    } else {
        re = false;
    }
    return re;
}
bool list::prev(){
    bool re = true;;
    if(acT != 0){
        acT = acT->prev; 
    } else {
        re = false;			
    }
    return re;
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


/*
this function set the value to 2, 7, 8, 9
*/
void list::setKarta(int karta){	
    acT->karta = karta;
}	