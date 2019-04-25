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

enum LedState {LED_RIGHT,LED_STOP};
enum LedState eLedState = LED_STOP;
unsigned char ucStepCounter=0;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eLedState)
		{
			case LED_RIGHT:
				if(ucStepCounter>3)
				{
					ucStepCounter=0;
					eLedState = LED_STOP;
				}
				else
				{
					ucStepCounter++;
					LedStepRight();
				}
				break;
			case LED_STOP:
				if(eKeyboardRead()==BUTTON_0)
				{
					eLedState = LED_RIGHT;
				}
				break;
			default:{}
		}
		Delay(100);
	}
}
