#ifndef listA_H
#define listA_H
#include "kartA.h"

class listA {
   public:
        listA();
        virtual ~listA();
        kartA* toP;			// wska�nik do elementu pierwszego
        kartA* boT;			// wska�nik do elementu ostatniego
        kartA* acT;			// act przy przesuwaniu ustawia na aktualny element, kt�ry wynika� z 'next' czy 'previous'

		unsigned int Id;
        double stepHST;
        void push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inKarta);



        bool top();			 // id� na koniec
        bool bot();			 // id� na poczatek
       
    protected:
    private:
};

#endif // listA_H














