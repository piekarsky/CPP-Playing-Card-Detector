#ifndef card_H
#define card_H
#include <math.h>
#define M_PI  (3.14159265)
#define HIST_VO_    (  256)			 // number of items in the histogram
#define HIST_VOL    ( 1024)			 // number of distances (radius) from the center to the edges of the rectangle
								 

class kartA {
   public:
        kartA* prev;		// prev i next wskazuj¹ na obiekty karta
		kartA* next;
        int karta;			// wartoœci kart [2, 7, 8, 9]
        int kolor;			// kolory kart [0, 1, 2, 3]
        int color;			// kolory kart 0, 1 [czerwony, czarny]

		// karty s¹ to obiekty zdefiniowane przez prostok¹ty
	
		unsigned int inKarta;		// wskaŸnik Id karty 'Matki'
		// dla podobiektów (symboli) inKarta odpowiada Id karty
		unsigned int Id; 
        unsigned int blX, blY, trX, trY;
		double oO, aR, xC, yC;		// oO = obwód, aR = pole, xC, yC = wspó³rzêdne œrodka karty
        double ffT[HIST_VO_];
        kartA();
        virtual ~kartA();
        unsigned int getRad();

    protected:
    private:
};

#endif 

