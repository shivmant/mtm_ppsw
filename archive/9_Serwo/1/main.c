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

enum DetectorState {INACTIVE,ACTIVE,CALLIB};

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
	static enum DetectorState eDetectorState;
	
	switch(eDetectorState)
	{
		case ACTIVE:
			while(1){};
			break;
		case INACTIVE:
			eDetectorState=CALLIB;
			break;
		case CALLIB:
			LedStepLeft();
			eDetectorState=eReadDetector();
			break;
	}
}

int main ()
{
	unsigned int iMainLoopCtr;
	
	Timer0Interrupts_Init(50000, &Automat);
	LedInit();
	ButtonInit();
	DetectorInit();

	while(1){
	 	iMainLoopCtr++;
	}
}
