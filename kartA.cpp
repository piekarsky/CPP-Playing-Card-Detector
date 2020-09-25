#include "kartA.h"
#include <math.h>

// inicjowanie obiektu 'karta' zwi�zane jest z zerowaniem wskaznik�w
kartA::kartA(){
    prev = 0;
    next = 0;
}

kartA::~kartA(){
    ;
}

// podaje �rednic� karty 
unsigned int kartA::getRad(){
    unsigned int W = trX - blX;		// d�ugo�� przek�tnej
    unsigned int H = trY - blY;
    return (unsigned int )floor(pow((float)W * (float)W + (float)H * (float)H, 0.5));
}


