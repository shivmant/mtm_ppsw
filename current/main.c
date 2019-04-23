#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiTimeInMs)
{
	
	unsigned int uiMsCounter;
	unsigned int uiTimeCounter;
	
	for(uiMsCounter=0; uiMsCounter<uiTimeInMs; uiMsCounter++)
	{
		for(uiTimeCounter=0; uiTimeCounter<3249; uiTimeCounter++){}
	}
}

int main()
{

	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eKeyboardRead())
		{
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			case RELASED:
				break;
			default:{}
		}
		Delay(500);
	}
	return 1;
}
