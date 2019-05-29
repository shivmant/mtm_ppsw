#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"
#include "timer_interrupts.h"

#define DETECTOTOR_bm (1<<10)

void DetectorInit()
{
	IO0DIR=IO0DIR&(~DETECTOTOR_bm);
}

enum DetectorState {INACTIVE,ACTIVE};

enum DetectorState eReadDetector()
{
	if((IO0PIN & DETECTOTOR_bm) == 0)
	{
		return ACTIVE;
	}
	else
	{
		return INACTIVE;
	}
}

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

struct Servo sServo;

void Automat()
{
	switch(sServo.eState)
	{
		case CALLIB:
			
			sServo.uiCurrentPosition=0;
			sServo.uiDesiredPosition=0;
			sServo.eState=IDLE;
			break;
		case IDLE:
			while(sServo.uiCurrentPosition == sServo.uiDesiredPosition)
			{
				if(eKeyboardRead()==BUTTON_0)
				{
					sServo.eState=CALLIB;
				}
				else if(eKeyboardRead()==BUTTON_1)
				{
					sServo.uiDesiredPosition=12;
					sServo.eState=IN_PROGRESS;
				}
				else if(eKeyboardRead()==BUTTON_2)
				{
					sServo.uiDesiredPosition=24;
					sServo.eState=IN_PROGRESS;
				}
				else if(eKeyboardRead()==BUTTON_3)
				{
					sServo.uiDesiredPosition=36;
					sServo.eState=IN_PROGRESS;
				}
			}
			break;
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition > sServo.uiDesiredPosition)
			{
				sServo.uiCurrentPosition--;
				LedStepRight();
			}
			else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition)
			{
				sServo.uiCurrentPosition++;
				LedStepLeft();
			}
			else if(sServo.uiCurrentPosition == sServo.uiDesiredPosition)
			{
				sServo.eState=IDLE;
			}
			break;
	}
}

int main ()
{
	unsigned int iMainLoopCtr;
	
	Timer0Interrupts_Init(50000, &Automat);
	LedInit();
	ButtonInit();
	DetectorInit();

	while(1){
	 	iMainLoopCtr++;
	}
}
