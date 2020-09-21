#include "lipa.h"
#include <iostream>
#include <stack>
#include <math.h>
#include "list.h"


using namespace std;


Image3CH in(1936, 1216);
Image1CH dst(in.width(), in.height());
Image1CH tst(2600, 2460);
Image3CH sym3(SYM_W, SYM_H);
Image1CH sym1(SYM_W, SYM_H);



void grayscale(Image3CH & in, Image1CH & out) {		// konwertowanie obrazu do skali szaro�ci	
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

/*
funkcja znajduje karty i zakre�la je prostok�tami
*/
void findCard(Image1CH &dst){		
	// algorytm wype�nienia powodziowego

	unsigned int ccC;
	stack<unsigned int> stos;
    bool go = true, goKart = true;
	int x0 = -1, y0 = -1;
	double intens = 0.0;
	unsigned int x, y, x1, y1, i, j, k, xbl, ybl, xtr, ytr, iD, I = 0, J = 0;
	while(goKart){			 // znajduje ziarno
        go = true;
        for (i = 0; i < dst.width(); i++) {
            if (go) {
                for (j = 0; j < dst.height(); j++) {
                    if (dst(i, j).I() > 0.8) {
                        intens = 0.0;
                        for (int n = 0; n < 5; n++) {
                            for (int m = 0; m < 5; m++) {
                                intens += dst((i  > n-2) ? i-n + 2: i, (j > m-2) ? j - m+2 : j).I();
                            }
                        }
                        if(intens > 5.0){
                            y0 = j; x0 = i;				// x0, y0 - wsp�rz�dne ziarna
                            go = false; break;
                        }

                    }
                }

            }
        }
		
		xbl = 10000; ybl = 10000; xtr = 0; ytr = 0; 
        if (x0 >= 0 && y0 >= 0) {
            stos.push(x0);		 // x0 i y0 na stos 
            stos.push(y0);
            bool gooo = true;
            while (gooo) {
                y = stos.top(); stos.pop(); x = stos.top(); stos.pop();		// pobiera ze stosu x i y
				

			   // liczy najmniejsze i najwi�ksze warto�ci
			   // najmniejsze to bottom left, a najwi�ksze to top right
                xbl = (x < xbl) ? x : xbl;	ybl = (y < ybl) ? y : ybl;
                xtr = (x > xtr) ? x : xtr;	ytr = (y > ytr) ? y : ytr;

						
				dst(x, y).I() = iNkar;
                for (k = 0; k < 8; k++) {				    // 8 bo zgodnie z o�miosp�jno�ci�
                    x1 = x + xofst[k]; 	y1 = y + yofst[k];
                    if (dst(x1, y1).I() > 0.9) {			// je�eli ten kolor ma warto�� intensywno�ci wieksz� ni� bia�y to idzie na stos
                        stos.push(x1);
                        stos.push(y1);
                    }
                }
                gooo = !stos.empty();
            }
					
            xtr += 1; ytr += 1;
            xbl -= 2; ybl -= 2;
            lista->push(xbl, ybl, xtr, ytr, 0);
            x0 = -1; y0 = -1; 
        } else {
            goKart = false;
        }
	}


int main(){

	// 0 pik   [2]
	// 1 kier  [7]
	// 2 trefl [9]
	// 3 karo  [8]

		
	in.LoadImage("img\\ideal.jpg", LPL_LOAD_FITTED);		 // wczytanie idealnego zdj�cia
	in.ShowImage("Original");
	
	grayscale(in, dst);
	binarization(dst);
	
	return 0;
}
