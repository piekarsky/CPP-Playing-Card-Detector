#include "listA.h"
#include <math.h>
#include <iostream>



listA::listA(){
    toP = 0;
    boT = 0;
    acT = 0;
    Id = 0;
    stepHST = 1.0 / (double)HIST_VO_;
}


listA::~listA(){
    ;
}



void listA::push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inKarta){
	
	// push - wstawia nowy element (bottomleft, topright i inKarta)
	
	kartA* karta = new kartA();		  // inicjuje nowy obiekt typu 'karta'
    if(toP == 0)toP = karta;
    Id++;							  // inkrementuje id
    karta->blX = blX;
    karta->blY = blY;
    karta->trX = trX;
    karta->trY = trY;
    karta->next = boT;				  // karta next = bot bo ustawia wskaźnik na początek
    karta->Id   = Id;
    karta->inKarta  = inKarta;
    if(karta->next != 0)karta->next->prev = karta;
    karta->prev  = 0;
    karta->karta = 0;
    boT = karta; 
    acT = karta;					  // indeks do utworzonego obiektu karta
    for(unsigned int i = 0; i < HIST_VO_; i++){
        karta->ffT[i] = 0.0;		  // zeruje tę macierz po to żeby można było dodawać elementy przy histogramie
    }
}
bool listA::top(){ 
    bool re = true;;
    if(boT != 0){
        acT = toP;
    } else {
        re = false;			// lista jest pusta
    }
    return re;
}
bool listA::bot(){
    bool re = true;
    if(boT != 0){
        acT = boT;
    } else {
        re = false;
    }
    return re;
}
bool listA::prev(){
    bool re = true;;
    if(acT != 0){
        acT = acT->prev; 
    } else {
        re = false;			
    }
    return re;
}
bool listA::next(){
    bool re = true;
    if(acT != 0){
        acT = acT->next;	 // jeżeli ten aktualny element istnieje to wtedy ustawia wskaźnik na ten, który jest następny

        re = acT != 0;		 // jeżeli jest różne od zera to istnieje jakiś następnik, a jeżeli nie to była to ostatnia karta
    } else { 
        re = false;		     // fałsz jest wtedy kiedy act jest równy zero
    }
    return re;
}
bool listA::empty(){
    return (toP == 0);		 // top jest zero kiedy lista jest pusta
}

void listA::get(unsigned int &blX, unsigned int &blY, unsigned int &trX, unsigned int &trY, unsigned int &Id){
    blX     = acT->blX;
    blY     = acT->blY;
    trX     = acT->trX;
    trY     = acT->trY;
    Id      = acT->Id;
}

void listA::setKarta(int karta){	 // ustawia wartość karty 2, 7, 8, 9
    acT->karta = karta;
}	