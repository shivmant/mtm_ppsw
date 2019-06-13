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

char cCommand[RECIEVER_SIZE];
extern unsigned char ucTokenNr;
extern struct Token asToken[MAX_TOKEN_NR];

int main ()
{
	//extern char cOdebranyZnak;
	//extern struct RecieverBuffer sRecieverBuffer;
	
	//ServoInit(50);
	UART_InitWithInt(9600);
	while(1)
	{
		if(eReciever_GetStatus()==READY)
		{
			Reciever_GetStringCopy(cCommand);
			DecodeMsg(cCommand);
			if((ucTokenNr > 0)&&(asToken[0].eType == KEYWORD))
			{
				switch(asToken[0].uValue.eKeyword)
				{
					case CLB:
						ServoCallib();
						break;
					case GOTO:
						if(asToken[1].eType == NUMBER)
						{
							ServoGoTo(asToken[1].uValue.uiNumber);
						}
						break;
				}
			}
		}
	}
}
