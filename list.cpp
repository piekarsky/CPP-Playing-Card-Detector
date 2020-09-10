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


