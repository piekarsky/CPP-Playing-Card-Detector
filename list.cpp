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



void list::push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int idCard){
	
	// push - inserts a new element (bottomleft, topright and idCard)
	
	card* card = new card();		 	 
   	if(toP == 0)toP = card;
 	Id++;					                   
  	card->blX = blX;
   	card->blY = blY;
   	card->trX = trX;
 	card->trY = trY;
  	card->next = boT;				  
 	card->Id   = Id;
    card->idCard  = idCard;
   	
	if(card->next != 0)card->next->prev = card;
    	card->prev  = 0;
    	card->card = 0;
   	boT = card; 
  	acT = card;					 
    	for(unsigned int i = 0; i < HIST_VO_; i++){
        		card->ffT[i] = 0.0;				  // reset this matrix to add items to the histogram
  	}
}


bool list::top(){ 
    	bool re = true;;
    	if(boT != 0){
       	 	acT = toP;
    	} else {
        		re = false;			
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

        re = acT != 0;		 // if it is not equal to zero then there is a successor, and if not then it was the last card
    } else { 
        re = false;		     // false is when 'act' is equal to zero
    }
    return re;
}


bool list::empty(){
    return (toP == 0);		 // top is equal to zero when the list is empty
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
void list::setCard(int card){	
    acT->card = card;
}

void list::setSuit(int card){	 //  set the suit of the card 
    acT->suit = card;
}
void list::setColor(int color){	 // set the color of the card 
    acT->color = card;
}

int list::getCard(){			     // get the value from the current card
    return acT->card;
}

int list::getColor(){				 // get the suit of the current card
    return acT->color;
}
int list::getColor(){ 
    return acT->card;
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


bool list::del(unsigned int Id){
	bool re = goId(Id); 
	if(re){
        del();
    }
	return re;
}

bool list::del(){
	bool re = true;
	card* temp = acT;
    if(acT->prev != 0){					 //         <--------------    prev
		acT->prev->next = acT->next;	 //     prev[del]  | for del | next[del]
        if(acT->next != 0){				 //       next        --------->
            acT->next->prev = acT->prev;
        }
    } else {
        if(acT->next != 0){
            acT->next->prev = 0;
            boT = acT->next;
        }
    }
    acT->next = 0; acT->prev = 0; acT->Id = 0;
    delete temp;
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


bool list::top(){ 
    bool re = true;;
    if(boT != 0){
        acT = toP;
    } else {
        re = false;			
    }
    return re;
}
