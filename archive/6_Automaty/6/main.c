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

enum LedState {LED_LEFT,LED_RIGHT,LED_STOP};
enum LedState eLedState = LED_RIGHT;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
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
			default:{}
		}
		Delay(100);
	}
}
