#ifndef kartA_H
#define kartA_H
#include <math.h>
#define M_PI  (3.14159265)
#define HIST_VO_    (  256)			 // iloœæ pozycji w histogramie
#define HIST_VOL    ( 1024)			 // iloœæ odleg³oœci (promieni) od œrodka do brzegów prostok¹ta
								 

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

