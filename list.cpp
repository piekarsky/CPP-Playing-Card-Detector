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
	
	card* Card = new card();		 	 // initialize a new 'card' object
   	if(toP == 0)toP = karta;
 	Id++;					                   // increment the id
  	Card->blX = blX;
   	Card->blY = blY;
   	Card->trX = trX;
 	Card->trY = trY;
  	Card->next = boT;				  // card next = bot because it sets the pointer to the beginning
 	Card->Id   = Id;
    	Card->inCard  = inCard;
   	
	if(Card->next != 0)Card->next->prev = Card;
    	Card->prev  = 0;
    	Card->Card = 0;
   	boT = Card; 
  	acT = Card;					  // index to the created object tab
    	for(unsigned int i = 0; i < HIST_VO_; i++){
        		Card->ffT[i] = 0.0;				  // reset this matrix to add items to the histogram
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
void list::setCard(int cardValue){	
    acT->cardValue = card;
}

void list::setCardColor(int cardValue){	 // set card color to 0, 1, 2, 3
    acT->cardValue = card;
}
void listA::setColor(int color){	 // set card color to 0, 1 [czarny, czerwony]
    acT->Color = card;
}

int list::getCard(){			     // get the value from the current card
    return acT->cardValue;
}

int list::getColor(){				 // get the suit of the current card
    return acT->color;
}
int list::getColor(){ 
    return acT->cardValue;
}


bool list::next(unsigned int inCard){
    bool re = false;
    if(acT != 0){ 
        while(acT->next != 0){
            acT = acT->next;
            if(acT->idCard == inCard){
                re = true;
                break;
            }
        }
    }
    return re;
}

bool list::bot(unsigned int inCard){
    bool re = false;
    if(boT != 0){
        acT = boT;
        if(acT->idCard == inCard){
            re = true;
        } else {
            re = next(inCard); 
        }
    } else {
        re = false;			
    }
    return re;
}



unsigned int list::getId(){		// get the id from the current element
    return acT->Id;  
}

bool list::goId(unsigned int Id){			// go to the specified id
	bool re = false;
	if(boT != 0){
        acT = boT;
        if(acT->Id == Id){
            re = true;
        } else {
            while(acT->next != 0){
                acT = acT->next;
                if(acT->Id == Id){
                    re = true;
                    break;
                }
            }
        }
    } else {
        re = false;
    }
    return re;
}

void list::getC(double &xC, double &yC) {
	xC = acT->xC;
	yC = acT->yC;
}
bool list::findCard(int card, int color) {
	bool re = false, go = true;
	if (bot(0)) {
		while (go) {
			if (acT->card == card && acT->color == color) {
				re = true;
				break;
			}
			go = next(0);
		}
	}
	return re;
}
