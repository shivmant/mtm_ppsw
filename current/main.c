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
enum LedState eLedState = NO_MOVE;
unsigned char StepCounter;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eLedState)
		{
			case LED_RIGHT:
				if(StepCounter<=3)
				{
					StepCounter++;
					LedStepRight();
				}
				else
				{
					eLedState = NO_MOVE;
				}
				break;
			case NO_MOVE:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = LED_RIGHT;
					StepCounter = 0;
				}
				break;
			default:{}
		}
	}
}
