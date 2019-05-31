#include "led.h"
#include "keyboard.h"
#include "timer.h"
#include "timer_interrupts.h"
#include "servo.h"
#include "uart.h"
#include <LPC21xx.H>

int main ()
{
	extern char cOdebranyZnak;
	unsigned char currentPosition;
	ServoInit(50);
	UART_InitWithInt(9600);
	while(1)
	{
		switch(cOdebranyZnak)
		{
			case '1':
				currentPosition++;
				ServoGoTo(12*currentPosition);
				cOdebranyZnak='\0';
				break;
			case '2':
				currentPosition=2;
				ServoGoTo(24);
				break;
			case '3':
				currentPosition=3;
				ServoGoTo(36);
				break;
			case 'c':
				currentPosition=0;
				ServoCallib();
				break;
		}
		switch(eKeyboardRead())
		{
			case BUTTON_0:
				ServoCallib();
				break;
			case BUTTON_1:
				ServoGoTo(12);
				break;
			case BUTTON_2:
				ServoGoTo(24);
				break;
			case BUTTON_3:
				ServoGoTo(36);
				break;
			case RELASED:
				break;
		}
	}
}
