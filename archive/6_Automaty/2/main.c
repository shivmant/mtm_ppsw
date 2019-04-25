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

enum LedState {STATE0,STATE1,STATE2,STATE3,STATE4,STATE5};
enum LedState eLedState = STATE0;

int main()
{
	LedInit();
	ButtonInit();
	
	while(1)
	{
		switch(eLedState)
		{
			case STATE0:
				eLedState = STATE1;
				LedStepLeft();
				break;
			case STATE1:
				eLedState = STATE2;
				LedStepLeft();
				break;
			case STATE2:
				eLedState = STATE3;
				LedStepLeft();
				break;
			case STATE3:
				eLedState = STATE4;
				LedStepRight();
				break;
			case STATE4:
				eLedState = STATE5;
				LedStepRight();
				break;
			case STATE5:
				eLedState = STATE0;
				LedStepRight();
				break;
			default:{}
		}
		Delay(500);
	}
}
