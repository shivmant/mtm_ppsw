#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define MR0_INTERRUPT_FLAG (1<<0)
#define INTERRUPT_ON_MR0 (1<<0)
#define RESET_ON_MR0 (1<<1)
#define STOP_ON_MR0 (1<<2)

void InitTimer0(void)
{
	T0TCR=T0TCR|COUNTER_ENABLE;					//wlaczamy timer
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR=T0TCR|COUNTER_RESET;					//resetujemy timer
	T0TCR=T0TCR&~COUNTER_RESET;					//przywracamy rejestr kontroli do poprzedniego stanu, aby timer mogl liczyc dalej	
	while(uiTime*15>T0TC){}							//petla wykonujaca sie dopóki timer nie wyrówna sie z czasem podanym w argumencie funkcji
}

void InitTimer0Match0(unsigned int uiDelayTime)
{
	T0TCR=T0TCR|COUNTER_ENABLE;					//wlaczamy timer
	T0MR0=uiDelayTime*15;								//ustawiamy czas do którego timer bedzie porownywany
	T0MCR=T0MCR|RESET_ON_MR0;						//ustawiamy w rejestrze kontroli porownan reset timera przy zrównaniu z MR0
	T0MCR=T0MCR|INTERRUPT_ON_MR0;				//ustawiamy w rejestrze kontroli porownan przerwanie przy zrównaniu timera z MR0
}

void WaitONTimer0Match0(void)
{
	T0IR=T0IR|MR0_INTERRUPT_FLAG;				//ustawiamy w rejestrze przerwan bit przerwania przy MR0 (po ustaweniu 1 nastepuje reset i stan 0)
	T0TCR=T0TCR|COUNTER_RESET;					//resetujemy time
	T0TCR=T0TCR&~COUNTER_RESET;					//przywracamy rejestr kontroli do poprzedniego stanu, aby timer mogl liczyc dalej	
	while(T0IR==0){}										//petla wykonujaca sie dopóki nie nastapi przerwanie przy zrownaniu MR0 z timerem (przy przerwaniu 1)
}
