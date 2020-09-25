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
        bool prev();
        bool next();
        bool empty();
        void get(unsigned int &blX, unsigned int &blY, unsigned int &trX, unsigned int &trY, unsigned int &Id);
        void listA::setKarta(int karta);
        void listA::setKolor(int karta);
        void listA::setColor(int karta);
        int listA::getKarta();
        int listA::getKolor();
        int listA::getColor();

        bool next(unsigned int inKart); 
        bool bot(unsigned int inKart);

		unsigned int getId();				// pobera id karty
        bool goId(unsigned int Id);			// wykonuje skok do okreúlonego id
        bool del(unsigned int Id);			// usuwa element z listy o konkretnym id
        bool del();							// usuwa act
		