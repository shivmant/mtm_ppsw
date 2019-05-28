#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"
#include "timer_interrupts.h"

#define DETECTOTOR_bm (1<<10)

void DetectorInit()
{
	IO0DIR=IO0DIR&(~DETECTOTOR_bm);
}

enum DetectorState {ACTIVE,INACTIVE,CALLIB};

enum DetectorState eReadDetector()
{
	if((IO0PIN & DETECTOTOR_bm) == 0)
	{
		return ACTIVE;
	}
	else
	{
		return INACTIVE;
	}
}

enum LedState {LED_LEFT,LED_RIGHT,LED_STOP};

void Automat()
{
	static enum LedState eLedState;
	
	switch(eLedState)
	{
		case LED_LEFT:
			if(eKeyboardRead()==BUTTON_1)
			{
				eLedState = LED_STOP;
			}
			else
			{
				LedStepLeft();
			}
			break;
		case LED_RIGHT:
			if(eKeyboardRead()==BUTTON_1)
			{
				eLedState = LED_STOP;
			}
			else
			{
				LedStepRight();
			}
			break;
		case LED_STOP:
			if(eKeyboardRead()==BUTTON_0)
			{
				eLedState = LED_LEFT;
			}
			else if(eKeyboardRead()==BUTTON_2)
			{
				eLedState = LED_RIGHT;
			}
			break;
	}
}

int main ()
{
	unsigned int iMainLoopCtr;
	
	Timer0Interrupts_Init(250000, &Automat);
	LedInit();
	ButtonInit();

	while(1){
	 	iMainLoopCtr++;
	}
}
