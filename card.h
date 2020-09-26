#ifndef card_H
#define card_H
#include <math.h>
#define M_PI  (3.14159265)
#define HIST_VO_    (  256)			 // number of items in the histogram
#define HIST_VOL    ( 1024)			 // number of distances (radius) from the center to the edges of the rectangle
								 

class kartA {
   public:
        kartA* prev;		// prev i next wskazuj� na obiekty karta
		kartA* next;
        int karta;			// warto�ci kart [2, 7, 8, 9]
        int kolor;			// kolory kart [0, 1, 2, 3]
        int color;			// kolory kart 0, 1 [czerwony, czarny]

		// karty s� to obiekty zdefiniowane przez prostok�ty
	
		unsigned int inKarta;		// wska�nik Id karty 'Matki'
		// dla podobiekt�w (symboli) inKarta odpowiada Id karty
		unsigned int Id; 
        unsigned int blX, blY, trX, trY;
		double oO, aR, xC, yC;		// oO = obw�d, aR = pole, xC, yC = wsp�rz�dne �rodka karty
        double ffT[HIST_VO_];
        kartA();
        virtual ~kartA();
        unsigned int getRad();

    protected:
    private:
};

#endif 

