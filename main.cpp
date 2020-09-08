#include "lipa.h"
#include <iostream>
#include <stack>
#include <math.h>


using namespace std;


Image3CH in(1936, 1216);
Image1CH dst(in.width(), in.height());
Image1CH tst(2600, 2460);
Image3CH sym3(SYM_W, SYM_H);
Image1CH sym1(SYM_W, SYM_H);



void grayscale(Image3CH & in, Image1CH & out) {		// konwertowanie obrazu do skali szaroœci	
	for (int i = 0; i < in.width(); i++) {
		for (int j = 0; j < in.height(); j++) {
			out(i, j).Intensity() = (in(i, j).Red() + in(i, j).Green() + in(i, j).Blue()) / 3;
		}
	}
}  


void binarization(Image1CH & in) {				// progowanie obrazu		
	for (int i = 0; i < in.width(); i++) {
		for (int j = 0; j < in.height(); j++) {
			if (in(i, j).I() > 0.451) {
				in(i, j).I() = 1;
			}
			else {
				in(i, j).I() = 0;
			}
		}
	}
}



int main(){

	// 0 pik   [2]
	// 1 kier  [7]
	// 2 trefl [9]
	// 3 karo  [8]

		
	in.LoadImage("img\\ideal.jpg", LPL_LOAD_FITTED);		 // wczytanie idealnego zdjêcia
	in.ShowImage("Original");
	
	grayscale(in, dst);
	binarization(dst);
	
	return 0;
}
