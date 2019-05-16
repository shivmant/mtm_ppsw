#include "led.h"
#include "keyboard.h"
#include "timer.h"

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
	//InitTimer0();
	InitTimer0Match0(1000000);
	
	while(1)
	{
		LedStepLeft();
		LedStepLeft();
		LedStepLeft();
		WaitONTimer0Match0();
		//WaitOnTimer0(1000000);
	}
}
