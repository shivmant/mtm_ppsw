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

enum LedState {LED_LEFT,LED_RIGHT};
enum LedState eLedState = LED_RIGHT;
unsigned char ucStepCounter=0;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eLedState)
		{
			case LED_LEFT:
				if(ucStepCounter>3)
				{
					ucStepCounter=0;
					eLedState = LED_RIGHT;
				}
				else
				{
					ucStepCounter++;
					LedStepRight();
				}
				break;
			case LED_RIGHT:
				if(ucStepCounter>3)
				{
					ucStepCounter=0;
					eLedState = LED_LEFT;
				}
				else
				{
					ucStepCounter++;
					LedStepRight();
				}
				break;
			default:{}
		}
		Delay(100);
	}
}
