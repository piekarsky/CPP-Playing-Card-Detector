#ifndef list_H
#define list_H
#include "card.h"

class list {
  	public:
		list();
        		virtual ~list();
        		card* toP;				// pointer to the first element
        		card* boT;			// pointer to the last element
        		card* acT;			// act on shift sets to the current element that resulted from 'next' or 'previous'

        		unsigned int Id;
        		double stepHST;
        		void push(unsigned int blX, unsigned int blY, unsigned int trX, unsigned int trY, unsigned int inCard);



        		bool top();			 // go to the end
       	 	bool bot();			 // go to the beginning
        		bool prev();
        		bool next();
        		bool empty();
        		void get(unsigned int &blX, unsigned int &blY, unsigned int &trX, unsigned int &trY, unsigned int &Id);
        		void list::setCard(int Card);
        		void list::setCardColor(int Card);
        		void list::setColor(int Card);
        		int list::getCard();
        		int list::getCardColor();
        		int list::getColor();

        		bool next(unsigned int inCard); 
    		bool bot(unsigned int inCard);

        		unsigned int getId();			// download the card id
        		bool goId(unsigned int Id);		// jumps to the specified id
       		bool del(unsigned int Id);		// removes an item from the list with a specific id
     		bool del();				
		
        		unsigned int getRad();
    		unsigned int getCard();
      		unsigned int getInKarta();
   		unsigned int cntInKart(unsigned int inCard);
     		double getSD(unsigned int inCard);
    		unsigned int getMax(unsigned int inCard);
     		void setFFTarr(double f);
      		void setFFTarr_(double f, double ffT[HIST_VO_]);
        		double getD2(unsigned int Id1, unsigned int Id2);
       		double getFFTarr(unsigned int i);
     		double testD2(double ffT[HIST_VO_], double ggT[HIST_VO_]);
		void setOo(double t);
		void setAr(double t);
		void setC(double xC, double yC);
		void getC(double &xC, double &yC);
		double getAr();
		double getOo();
      		bool findCard(int card, int color);	
    protected:
    private:
};

#endif // list_H

