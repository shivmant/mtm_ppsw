#include <LPC21xx.H>
#include "led.h"

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

enum StepDirection {RIGHT, LEFT};

void LedInit()
{
	
	IO1DIR = 0x000F0000;
}

void LedOn(unsigned char ucLedIndeks)
{
	
	IO1CLR = 0x000F0000;
	switch(ucLedIndeks)
	{
		case 0:
		
			IO1SET = LED0_bm;
			break;
		
		case 1:
		
			IO1SET = LED1_bm;
			break;
		
		case 2:
		
			IO1SET = LED2_bm;
			break;
		
		case 3:
		
			IO1SET = LED3_bm;
			break;
		
		default:
			break;
	}
}

void LedStep(enum StepDirection enDirection)
{
	
	static unsigned int uiLedLight;
	
	if(enDirection == LEFT)
	{
		uiLedLight++;
	}
	if(enDirection == RIGHT)
	{
		uiLedLight--;
	}
	LedOn(uiLedLight%4);
}

void LedStepLeft()
{
	LedStep(LEFT);
}

void LedStepRight()
{
	LedStep(RIGHT);
}
