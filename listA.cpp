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


