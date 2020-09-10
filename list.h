#ifndef list_H
#define list_H


class listA {
   public:
        listA();
        virtual ~listA();
        kartA* toP;			// wskaźnik do elementu pierwszego
        kartA* boT;			// wskaźnik do elementu ostatniego
        kartA* acT;			// act przy przesuwaniu ustawia na aktualny element, który wynikał z 'next' czy 'previous'

		unsigned int Id;
        double stepHST;
        void push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inKarta);
