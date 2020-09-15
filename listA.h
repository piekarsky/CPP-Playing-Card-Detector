#ifndef listA_H
#define listA_H
#include "kartA.h"

class listA {
   public:
        listA();
        virtual ~listA();
        kartA* toP;			// wskaünik do elementu pierwszego
        kartA* boT;			// wskaünik do elementu ostatniego
        kartA* acT;			// act przy przesuwaniu ustawia na aktualny element, ktÛry wynika≥ z 'next' czy 'previous'

		unsigned int Id;
        double stepHST;
        void push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inKarta);



        bool top();			 // idü na koniec
        bool bot();			 // idü na poczatek
       
    protected:
    private:
};

#endif // listA_H














