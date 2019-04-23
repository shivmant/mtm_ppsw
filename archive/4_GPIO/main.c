#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define BUTTON0_bm (1<<4)
#define BUTTON1_bm (1<<6)
#define BUTTON2_bm (1<<5)
#define BUTTON3_bm (1<<7)

enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum StepDirection {RIGHT, LEFT};

void Delay(unsigned int uiTimeInMs)
{
	
	unsigned int uiMsCounter;
	unsigned int uiTimeCounter;
	
	for(uiMsCounter=0; uiMsCounter<uiTimeInMs; uiMsCounter++)
	{
		for(uiTimeCounter=0; uiTimeCounter<3249; uiTimeCounter++){}
	}
}

void LedInit()
{
	
	IO1DIR = IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
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

enum KeyboardState eKeyboardRead()
{
	
	if((IO0PIN & BUTTON0_bm) == 0)
	{
		return BUTTON_0;
	}
	else if((IO0PIN & BUTTON1_bm) == 0)
	{
		return BUTTON_1;
	}
	else if((IO0PIN & BUTTON2_bm) == 0)
	{
		return BUTTON_2;
	}
	else if((IO0PIN & BUTTON3_bm) == 0)
	{
		return BUTTON_3;
	}
	return RELASED;
}

void ButtonInit()
{
	
	IO0DIR=IO0DIR&(~(BUTTON0_bm|BUTTON1_bm|BUTTON2_bm|BUTTON3_bm));
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

int main()
{
	//unsigned int uiSteps;
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
		
		/*for(uiSteps=1;uiSteps<=9;uiSteps++)
		{
			LedStep(LEFT);
			Delay(500);
		}
		for(uiSteps=1;uiSteps<=9;uiSteps++)
		{
			LedStep(RIGHT);
			Delay(500);
		}*/
		/*switch(eKeyboardRead())
		{
			case BUTTON_0:
				LedOn(0);
				break;
			case BUTTON_1:
				LedOn(1);
				break;
			case BUTTON_2:
				LedOn(2);
				break;
			case BUTTON_3:
				LedOn(3);
				break;
			case RELASED:
				LedOn(4);
				break;
			default:{}
		}*/
	}
	return 1;
}
