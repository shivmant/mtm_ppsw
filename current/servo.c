#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOTOR_bm (1<<10)

struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

void DetectorInit()
{
	IO0DIR=IO0DIR&(~DETECTOTOR_bm);
}

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

struct Servo sServo;

void Automat()
{
	switch(sServo.eState)
	{
		case CALLIB:	
			if(eReadDetector()==INACTIVE)
			{
				LedStepRight();
			}
			else
			{
			sServo.eState=IDLE;
			}
			break;
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition)
			{
				sServo.eState=IN_PROGRESS;
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



void ServoInit(unsigned int uiServoFrequency)
{	
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init(1000000/uiServoFrequency, &Automat);
	ServoCallib();
}

void ServoCallib()
{
	sServo.eState = CALLIB;
	sServo.uiCurrentPosition=0;
	sServo.uiDesiredPosition=0;
	while(sServo.eState!=IDLE){}
}

void ServoGoTo(unsigned int uiPosition)
{
	sServo.uiDesiredPosition=uiPosition;
	sServo.eState=IN_PROGRESS;
	while(sServo.eState!=IDLE){}
}
