#include "lipa.h"
#include <iostream>
#include <stack>
#include <math.h>
#include <stdio.h>
#include "list.h"
#define iNkar  0.4
#define iNkli  0.7
#define iNkbo  0.8
#define iNksy  0.99
#define iNkto  0.01
#define SYM_W  44
#define SYM_H  44

using namespace std;

Image3CH in(1936, 1216);
Image1CH dst(in.width(), in.height());
Image1CH tst(2600, 2460);
Image3CH sym3(SYM_W, SYM_H);
Image1CH sym1(SYM_W, SYM_H);

list* listA;
unsigned int xofst[8], yofst[8];
double symHistS[4][HIST_VO_];
double oOhistS[4][2];


/*
this function converts an image to grayscale
*/
void grayscale(Image3CH & in, Image1CH & out) {			
	
	for (int i = 0; i < in.width(); i++) {
		for (int j = 0; j < in.height(); j++) {
			out(i, j).Intensity() = (in(i, j).Red() + in(i, j).Green() + in(i, j).Blue()) / 3;
		}
	}
}  



/*
this function performs an image thresholding
*/
void binarization(Image1CH & in) {					
	
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



void diffArr(double* arr) {
	
	for (unsigned int i = 0; i < HIST_VOL - 1; i++)arr[i] = arr[i + 1] - arr[i];
}



double dist(double xt, double yt, double xt1, double yt1) {
	
	double t = xt - xt1, s = yt - yt1;
	return pow(t * t + s * s, 0.5);
}


/*
this function creates a distance function (along the radius) of a symbol shape from the center of a rectangle that includes a symbol
*/
void getFFT_(Image1CH &dst, unsigned int Xbl, unsigned int Ybl, unsigned int Xtr, unsigned int Ytr, double arr[HIST_VOL], double ColBor, double &oO){
                 
	double  Y, t, _Y, xt = -1.0, yt = -1.0, fi, x, y, xt1 = -1.0, yt1 = -1.0,
                 xo = (double)Xbl + ((double)Xtr - (double)Xbl) * 0.5,	// xo, yo - coordinates of the geometric center of a rectangle enclosing a symbol
                 yo = (double)Ybl + ((double)Ytr - (double)Ybl) * 0.5,		 
                 PI2 = 2.0f*M_PI, Astep = PI2/(double)HIST_VOL, Pstep = Astep, Rad = 0.0;
                 unsigned int i, w, h, k = 0;
                 bool go;


	// Astep to PI2 by the accuracy with which these rays are determined (the angle by which the radius moves)

	for(i = 0; i < HIST_VOL; i++){
		fi = Astep * (double)i;		    // angles are proportional to [i]
        		x = cos(fi) + xo; y = sin(fi) + yo;
      		go = true;
		t = Pstep;
        		while(go){
			xt = xo + t*(x - xo);		     // xt, yt - coordinates of a point on a radiusu
            			yt = yo + t*(y - yo);		

			w = (unsigned int)floor(xt);	     // xt, yt - real coordinates of a point on a radius
         			h = (unsigned int)floor(yt);	

			// performs shape detection
			if (w < Xbl || w > Xtr || h < Ybl || h >Ytr) {
				arr[i] = _Y;
				xt = xt1; yt = yt1;
				go = false;
			} else {
				if(dst(w, h).I() == ColBor){			// je¿eli intensity bêdzie wykraczaj¹ce poza znak
					Y = pow(pow(xt - xo, 2.0) + pow(yt - yo, 2.0), 0.5);
					arr[i] = Y;
					Rad = (Y > Rad)?Y:Rad;
					_Y = Y;
					go = false;
				} else {
					t += Pstep;
				  }
           			 }
	}
		if (xt  < 0.0) { xt = 0.0; yt = 0.0; }
		if (xt1 < 0.0) { xt1 = xt; yt1 = yt; }
		oO += dist(xt, yt, xt1, yt1);
		xt1 = xt; yt1 = yt;
    }

	
    for(i = 0; i < HIST_VOL; i++){
        arr[i] /= Rad;
    }
	diffArr(arr);
}



void getFFT(Image1CH &dst, unsigned int Xbl, unsigned int Ybl, unsigned int Xtr, unsigned int Ytr, int I, unsigned int J){
    
	// detekcja kszta³tu - wartoœci zapisuje do macierzy z których tworzy histogram
	
	double arr[HIST_VOL], oO = 0.0;
    unsigned int i;
    getFFT_(dst, Xbl, Ybl, Xtr, Ytr, arr, iNkar, oO);
	lista->setOo(oO);
	for(i = 0; i < HIST_VOL; i++){
        lista->setFFTarr(arr[i]);
    }
    for(i = 0; i < HIST_VOL; i++){
        tst.DrawPoint(i + I*519, J*202 + ((int)floor(/*lista->getFFTarr[i]*/arr[i] * 200.0)));
    }
   //tst.ShowImage("FFT");		// wyœwietla histogram
	
}

/*
funkcja liczaca odchylenie standardowe odleg³oœci p-któw brzegowych figury(arr) do punktu wnêtrza figury (p(x, y))
= minimum dla œrodka figury 
*/
double getD2(double arr[HIST_VOL][2], double x, double y){
   	double s = 0.0, t, sM = 0.0, ar[HIST_VOL];
    unsigned int i;
    for(i = 0; i < HIST_VOL; i++){
        t = dist(x, y, arr[i][0], arr[i][1]);			
        sM += t; ar[i] = t;							// sumuje punkty bêd¹ce na obrze¿u karty
    }
    sM /= (double)HIST_VOL;
    for(i = 0; i < HIST_VOL; i++){
        t = sM - ar[i];			
        s += t*t;
    }
    return pow(s, 0.5);		// zwraca odchylenie standardowe
}



double getD2(double arr[HIST_VOL][2], double x, double y){
   	double s = 0.0, t, sM = 0.0, ar[HIST_VOL];
    unsigned int i;
    for(i = 0; i < HIST_VOL; i++){
        t = dist(x, y, arr[i][0], arr[i][1]);			
        sM += t; ar[i] = t;							// add up the points at the edge of the card
    }




/*
this function fills the area between the rectangle's edges and the card outline
*/
void colorBorder(Image1CH &dst, unsigned int Xbl, unsigned int Ybl, unsigned int Xtr, unsigned int Ytr){
	unsigned int i, j;
	for (i = Xbl+1; i < Xtr; i++){
        for (j = Ybl+1; j < Ytr; j++) {
            if(dst(i, j).I() == iNkar)break;
            if (dst(i, j).I() < 0.1){
                dst(i, j).I() = iNkbo;
            }
        }
	}
	for (i = Xbl+1; i < Xtr; i++){
        for (j = Ytr-1; j > Ybl; j--) {
            if(dst(i, j).I() == iNkar)break;
            if (dst(i, j).I() < 0.1){
                dst(i, j).I() = iNkbo;
            }
        }
	}
	for (j = Ybl+1; j < Ytr; j++) {
        for (i = Xbl+1; i < Xtr; i++){
            if(dst(i, j).I() == iNkar)break;
            if (dst(i, j).I() < 0.1){
                dst(i, j).I() = iNkbo;
            }
        }
	}
	for (j = Ybl+1; j < Ytr; j++) {
        for (i = Xtr-1; i > Xbl; i--){
            if(dst(i, j).I() == iNkar)break;
            if (dst(i, j).I() < 0.1){
                dst(i, j).I() = iNkbo;
            }
        }
	}
}

/*
funkcja ta znajduje i oznacza symbole kart
*/
unsigned int findSign(Image1CH &dst, unsigned int Xbl, unsigned int Ybl, unsigned int Xtr, unsigned int Ytr, unsigned int Id, unsigned int &I, unsigned int &J){
	unsigned int ccC = 0;
	stack<unsigned int> stos;
    bool go = true, goKart = true, goCol;
	int x0 = -1, y0 = -1;
	unsigned int x, y, x1, y1, i, j, k, xbl, ybl, xtr, ytr, iD, cnt = 0, aR;
	
	while(goKart){			// znajduje ziarna
		
		// algorytm wyszukuje czarne elementy i wype³nia je bia³ym kolorem
		go = true; goCol = false;
        for (i = Xbl; i <= Xtr; i++) {
            if (go) {
                for (j = Ybl; j <= Ytr; j++) {
                    goCol = (dst(i, j).I() > 0.35 && dst(i, j).I() < 0.45) || goCol;
                    if(goCol){
                        if (dst(i, j).I() < 0.3) {
                            y0 = j; x0 = i;
                            go = false;
                            break;
                        }
                    }
                }
            }
						
        }
        if (x0 >= 0 && y0 >= 0) {
            stos.push(x0);
            stos.push(y0);
			bool gooo = true;
			xbl = 10000; ybl = 10000; xtr = 0; ytr = 0; aR = 0;
            while (gooo) {
                y = stos.top(); stos.pop(); x = stos.top(); stos.pop();
				xbl = (x < xbl) ? x : xbl;	ybl = (y < ybl) ? y : ybl;
                xtr = (x > xtr) ? x : xtr;	ytr = (y > ytr) ? y : ytr;
				if (dst(x, y).I() < 0.2) { dst(x, y).I() = iNksy; aR++; }
                for (k = 0; k < 8; k++) {
                    x1 = x + xofst[k]; 	y1 = y + yofst[k];
                    if(x1 > Xbl && x1 < Xtr && y1 > Ybl && y1 < Ytr){
                        if (dst(x1, y1).I() < 0.2){
                            stos.push(x1);
                            stos.push(y1);
                        }
                    }
                }
				gooo = !stos.empty();
            }
			lista->push(xbl-2, ybl-2, xtr+2, ytr+2, Id);		
			lista->setAr((double)aR);
            x0 = -1; y0 = -1;
        } else {
            goKart = false;
        }
	}

	
	// del is a method that removes redundant card symbols (those that are too small)
	bool goL = true; unsigned int ccc = lista->cntInKart(Id), mxx = lista->getMax(Id);
	if(ccc > 0){
        double SD = lista->getSD(Id);
        lista->bot(Id);

		
	// if the difference between the maximum symbol (the symbol with the largest diameter),
	// and the tested symbol is greater than the standard deviation, it removes the symbol





/*
funkcja znajduje karty i zakreœla je prostok¹tami
*/
void findCard(Image1CH &dst){		
	/*
		   xtr, ytr
	|   |  x| x |x |   |
	-----------------
	|   |  x| o |x |   |
	-----------------
	|   |  x| x |x |   |
	-----------------
	xbl, ybl                    
	x ---------------------->>
	
*/


	// algorytm wype³nienia powodziowego

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
                            				y0 = j; x0 = i;	 	// x0, y0 - wspó³rzêdne ziarna
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
				

			   // liczy najmniejsze i najwiêksze wartoœci
			   // najmniejsze to bottom left, a najwiêksze to top right
                xbl = (x < xbl) ? x : xbl;	ybl = (y < ybl) ? y : ybl;
                xtr = (x > xtr) ? x : xtr;	ytr = (y > ytr) ? y : ytr;

						
				dst(x, y).I() = iNkar;
                for (k = 0; k < 8; k++) {				    // 8 bo zgodnie z oœmiospójnoœci¹
                    x1 = x + xofst[k]; 	y1 = y + yofst[k];
                    if (dst(x1, y1).I() > 0.9) {			// je¿eli ten kolor ma wartoœæ intensywnoœci wieksz¹ ni¿ bia³y to idzie na stos
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


	bool goL = true, goD = true;

	dst.ShowImage("Playing card detection");		 

	goL = true;
    while(goL){
        goL = lista->bot() && goL;
        if(goL){
            goD = true;
            while(goD){
                goL = false;
                if(lista->getRad() < 200){		// zak³ada, ¿e karta ma promieñ wiêkszy ni¿ 200
                    lista->del();
                    goD = false;
                    goL = true;
                    break;
					
                } else {
                    goD = lista->next(); 
                }
            }
        }
    }
	
    goL = true;
    if(lista->bot(0)){
        while(goL){				// idzie na bottom(0) - idzie na pocz¹tek, pobiera z listy xbl, ybl, xtr, ytr i id i zwiêksza prostok¹t
            lista->get(xbl, ybl, xtr, ytr, iD);
            xtr += 2; ytr += 2;
			xbl -= 2; ybl -= 2;

	colorBorder(dst, xbl, ybl, xtr, ytr);   	 // wype³nia obszary pomiêdzy krawêdziami prostokata, a konturem karty
	dst.DrawLine(xbl, ybl, xtr, ybl, iNkli);
	dst.DrawLine(xbl, ybl, xbl, ytr, iNkli);
	dst.DrawLine(xtr, ybl, xtr, ytr, iNkli);
	dst.DrawLine(xtr, ytr, xbl, ytr, iNkli);
	lista->goId(iD);
	goL = lista->next(0);
        }
    }
	
    dst.ShowImage("Playing card detection");

	goL = true;
    if(lista->bot(0)){
		unsigned int aR = 0;
		double oO, X, Y;
		while(goL){
			lista->get(xbl, ybl, xtr, ytr, iD);
            			ccC = findSign(dst, xbl, ybl, xtr, ytr, iD, I, J);
			findCont(dst, xbl, ybl, xtr, ytr, oO, X, Y);
            			listA->goId(iD);
			listA->setCart(ccC);
			listA->setOo(oO);
			listA->setC(X, Y);
            			goL = listA->next(0);
        		}
    }
    dst.ShowImage("Symbol detection");


		
/*
function indentifies symbols by comparing the pattern and symbol histograms on the card
*/			

unsigned int setCarCol_(unsigned int Id){      
	bool goL = true;
	double T[4];
	int i0 = -1;
	unsigned int i, k = 0, ccC = 10000;
	for (i = 0; i < 4; i++)T[i] = 0.0;
	if(lista->bot(Id)){
	k = 0;
        	while(goL){
            		for (i = 0; i < 4; i++) {			         //testD2 checks for differences between the given symbol and the pattern
			T[i] += listA->testD2(listA->acT->ffT, symHistS[i]);     // symHist [i] - pattern histograms
           		}														      		goL = lista->next(Id);
            		k++;
      	}
	for (i = 0; i < 4; i++) {										
		if (T[i] < ccC) {
			i0 = i; ccC = T[i];				       // finds the smallest value
			}														   
		}
    	}
	return i0;
}





void setCarCol(){
	int i0;
	bool goL = true;
   	unsigned int xbl, ybl, xtr, ytr, iD;
  	  
	if(listA->bot(0)){
       		 while(goL){
         		  	listA->get(xbl, ybl, xtr, ytr, iD);
           			i0 = setCarCol_(iD);
          			listA->goId(iD);
			listA->setColor(i0);
          			goL = listA->next(0);
      		  }
  	 }
}


*/
void setSymArr() {			
	char symb[200];
	double symH_arr[HIST_VOL], oO = 0.0;

	unsigned int i, j, aR=0;
	for (i = 0; i < 4; i++) {			//color number [0, 1, 2, 3]
		for(j = 0; j < HIST_VO_; j++){
            			symHistS[i][j] = 0.0;		// pattern histograms
		}
		sprintf(symb, "img\\sym%d.jpg", i);

		sym3.LoadImage(symb, LPL_LOAD_FITTED);
		grayscale(sym3, sym1);
		binarization(sym1);

		getFFT_(sym1, 2, 2, SYM_W - 2, SYM_H - 2, symH_arr, 1.0, oO);		 // funkcja, która 'liczy' krzyw¹ konturu i obwód symbolu
		oOhistS[i][0] = oO;
		// sym1.ShowImage("Original");
		aR = findSignSym(sym1, 1, 1, SYM_W-1, SYM_H-1);
		oOhistS[i][1] = (double)aR;
	
		for(j = 0; j < HIST_VOL; j++){
            lista->setFFTarr_(symH_arr[j], symHistS[i]);
		}
	}
}



/*
tr = top right
bl = bottom left
			      xtr, ytr
		|   |  x| x |x |   |       
		--------------------------  |
		|   |  x| o |x |   |       
		--------------------------  |
		|   |  x| x |x |   |   
		--------------------------  |
	           xbl, ybl                    
											 */
void setArOfs(){
	xofst[0] =  1; yofst[0] = -1;
	xofst[1] =  1; yofst[1] =  0;
	xofst[2] =  1; yofst[2] =  1;
	xofst[3] =  0; yofst[3] =  1;
	xofst[4] = -1; yofst[4] =  1;
	xofst[5] = -1; yofst[5] =  0;
	xofst[6] = -1; yofst[6] = -1;
	xofst[7] =  0; yofst[7] = -1;
}



/* 
function writes (separately for each card) circumference, area and area / circumference ratio for symbols
and also lists total number of cards and total number of symbols in the photo
 */
void print() {		 
	bool goL = true, go;
	unsigned int Id;
	int lk = 0, ls = 0;			 // card and symbol counter
	double xC, yC;
	if (lista->bot(0)) {
		while (goL) {
			lista->getC(xC, yC);
			printf("Card = %1d  Color = %1d \tCircumference = %6.3f\t  oX = %4.1f  oY = %4.1f\n", listA->getCard(), 
			listA->getColor(), listA->getOo(),  xC, yC);Id = listA->getId();
			go = true;
			lk++;
		

	}
	goL = true;
	

	printf("Total number of cards in the photo: %1d\n Total number of all symbols in the photo: %1d\n", lk, ls);

}





int main(){

	
	printf("Color 0 = Spade \nColor 1 =Heart \nColor 2 = Club \nColor 3 = Diamond\n"); 

	listA = new list();
	setArOfs();
	setSymArr(); 
		
	in.LoadImage("img\\ideal.jpg", LPL_LOAD_FITTED);		 // load an original image
	in.ShowImage("Original");
	
	grayscale(in, dst);
	binarization(dst);
	findCard(dst);
	setCarCol();
	print();

	// mark the center of the 9 clubs card
	if (listA->findCard(9, 2)) {
		double xC, yC;
		listA->getC(xC, yC);
		printf("\nCard = %1d Color = %1d\nThe circumference of the card is %5.3f\nThe coordinates of the center of the card 
		oX = %5.1f  oY = %5.1f\n", listA->getCard(), listA->getColor(), listA->getOo(), xC, yC);
		in.DrawPoint(xC, yC, 1, 0, 0);
		
	}
	else {
		printf("Card not found");
	}
	system("pause");

	in.ShowImage("Original image with the center of the card");       // displays the original image with the center of the card selected

	
	return 0;
}
