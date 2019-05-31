//#include "led.h"
//#include "keyboard.h"
//#include "timer.h"
//#include "timer_interrupts.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include <LPC21xx.H>

#define TERMINATOR 0x0D
#define RECIEVER_SIZE 10
#define NULL 0

char komunikat[RECIEVER_SIZE];
enum KeywordCode enUARTcode;
char zmienna;

int main ()
{
	extern char cOdebranyZnak;
	extern struct RecieverBuffer sRecieverBuffer;
	
	ServoInit(50);
	UART_InitWithInt(9600);
	while(1)
	{
		if(eReciever_GetStatus()==READY)
		{
			Reciever_GetStringCopy(komunikat);
			eStringToKeyword(komunikat, &enUARTcode);
			switch(enUARTcode)
			{
				case CLB:
					ServoCallib();
					break;
				case LFT:
					ServoGoTo(32);
					break;
				case RGT:
					ServoGoTo(12);
					break;
				default:
					break;
			}
		}
	}
}
