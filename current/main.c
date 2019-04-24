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
enum LedState eLedState = LED_LEFT;
unsigned char counter;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eLedState)
		{
			case LED_LEFT:
				for(counter=0;counter<3;counter++)
				{
					LedStepLeft();
					Delay(500);
				}
				eLedState = LED_RIGHT;
				break;
			case LED_RIGHT:
				for(counter=0;counter<3;counter++)
				{
					LedStepRight();
					Delay(500);
				}
				eLedState = LED_LEFT;
				break;
			default:{}
		}
	}
	return 1;
}