#include "led.h"
#include "keyboard.h"
#include "timer.h"
#include "timer_interrupts.h"
#include "servo.h"
#include "uart.h"
#include <LPC21xx.H>

#define TERMINATOR 0x0D

int main ()
{
	enum eRecieverStatus {EMPTY, READY, OVERFLOW};
	extern struct RecieverBuffer sRecieverBuffer;
		//Zakladamy, ze RECIEVER_SIZE równa sie 4
	Reciever_PutCharacterToBuffer ('k');
	Reciever_PutCharacterToBuffer ('o');
	Reciever_PutCharacterToBuffer ('d');
	Reciever_PutCharacterToBuffer (TERMINATOR);
	// w buforze powinien znalezc sie lancuch znakowy “kod\0”,
	// status powinien równac sie READY, a cCharCtr 0.
	//sRecieverBuffer.eStatus=EMPTY;
	Reciever_PutCharacterToBuffer ('k');
	Reciever_PutCharacterToBuffer ('o');
	Reciever_PutCharacterToBuffer ('d');
	Reciever_PutCharacterToBuffer ('1');
	Reciever_PutCharacterToBuffer (TERMINATOR);
	// status powinien równac sie OVERFLOW
	
	/*extern char cOdebranyZnak;
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
				currentPosition=0;
				break;
			case '2':
				ServoGoTo(24);
				break;
			case '3':
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
	}*/
}
