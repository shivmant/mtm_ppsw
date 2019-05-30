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
	UART_InitWithInt(9600);
	while(1)
	{
		switch(cOdebranyZnak)
		{
			case '1':
				LedOn(0);
				break;
			case '2':
				LedOn(1);
				break;
			case '3':
				LedOn(2);
				break;
			case '4':
				LedOn(3);
				break;
			case 'c':
				LedOn(0);
				LedOn(1);
				LedOn(2);
				LedOn(3);
				break;
		}
	}
}
