#include "led.h"
#include "timer.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include <LPC21xx.H>

#define TERMINATOR 0x0D
#define NULL 0

char cCommand[RECIEVER_SIZE];
extern unsigned char ucTokenNr;
extern struct Token asToken[MAX_TOKEN_NR];
extern struct RecieverBuffer sRecieverBuffer;
unsigned int uiPosition;


//void BufferTest()
//{
//	//Zakladamy, ze RECIEVER_SIZE równa sie 4
//	Reciever_PutCharacterToBuffer ('k');
//	Reciever_PutCharacterToBuffer ('o');
//	Reciever_PutCharacterToBuffer ('d');
//	Reciever_PutCharacterToBuffer (TERMINATOR);
//	// w buforze powinien znalezc sie lancuch znakowy “kod\0”,
//	// status powinien równac sie READY, a cCharCtr 0.
//	sRecieverBuffer.eStatus = EMPTY;
//	Reciever_PutCharacterToBuffer ('k');
//	Reciever_PutCharacterToBuffer ('o');
//	Reciever_PutCharacterToBuffer ('d');
//	Reciever_PutCharacterToBuffer ('1');
//	Reciever_PutCharacterToBuffer (TERMINATOR);
//	// status powinien równac sie OVERFLOW
//}

int main ()
{
	UART_InitWithInt(9600);
	ServoInit(50);
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
						uiPosition=0;
						break;
					case GOTO:
						if(asToken[1].eType == NUMBER)
						{
							ServoGoTo(asToken[1].uValue.uiNumber);
							uiPosition=asToken[1].uValue.uiNumber;
						}
						else
						{
							LedOn(4);
						}
						break;
					case SHIFT:
						if(asToken[1].eType == NUMBER)
						{
							ServoGoTo(uiPosition+asToken[1].uValue.uiNumber);
							uiPosition=uiPosition+asToken[1].uValue.uiNumber;
						}
						else
						{
							LedOn(4);
						}
						break;
				}
			}
		}
	}
}
