#include "kartA.h"
#include <math.h>

// inicjowanie obiektu 'karta' zwi¹zane jest z zerowaniem wskazników
kartA::kartA(){
    prev = 0;
    next = 0;
}

kartA::~kartA(){
    ;
}

// podaje œrednicê karty 
unsigned int kartA::getRad(){
    unsigned int W = trX - blX;		// d³ugoœæ przek¹tnej
    unsigned int H = trY - blY;
    return (unsigned int )floor(pow((float)W * (float)W + (float)H * (float)H, 0.5));
}


