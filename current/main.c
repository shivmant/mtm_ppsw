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

enum LedState {LED_RIGHT,NO_MOVE};
enum LedState eLedState = LED_RIGHT;
//unsigned char StepCounter;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eLedState)
		{
			case LED_RIGHT:
				if(eKeyboardRead()==BUTTON_0)
				{
					eLedState = NO_MOVE;
				}
				else
				{
					LedStepRight();
				}
				break;
			case NO_MOVE:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = LED_RIGHT;
				}
				break;
			default:{}
		}
	}
}
