#ifndef list_H
#define list_H
#include "card.h"

class list {
   public:
        list();
        virtual ~list();
        card* toP;			// wskaünik do elementu pierwszego
        card* boT;			// wskaünik do elementu ostatniego
        card* acT;			// act przy przesuwaniu ustawia na aktualny element, ktÛry wynika≥ z 'next' czy 'previous'

        unsigned int Id;
        double stepHST;
        void push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inCard);



        bool top();			 // idü na koniec
        bool bot();			 // idü na poczatek
        bool prev();
        bool next();
        bool empty();
        void get(unsigned int &blX, unsigned int &blY, unsigned int &trX, unsigned int &trY, unsigned int &Id);
        void list::setCard(int Card);
        void list::setCardColor(int Card);
        void list::setColor(int Card);
        int list::getCard();
        int list::getKolor();
        int list::getColor();

        bool next(unsigned int inCard); 
        bool bot(unsigned int inCard);

        unsigned int getId();			// pobera id karty
        bool goId(unsigned int Id);			// wykonuje skok do okreúlonego id
        bool del(unsigned int Id);			// usuwa element z listy o konkretnym id
        bool del();				// usuwa act
		