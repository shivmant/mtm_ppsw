#include <LPC210X.H>
#include "uart.h"
#include "string.h"

/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

/************ Pin Control Register **********/
#define mP0_0_TX0_PIN_MODE                         (1<<0)
#define mP0_1_RX0_PIN_MODE                         (1<<2)

////////////// Zmienne globalne ////////////
char cOdebranyZnak;

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
			cOdebranyZnak = U0RBR;
			Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
      // narazie nic nie wysyłamy
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate)
{
   // UART0
   PINSEL0 = PINSEL0 | mP0_1_RX0_PIN_MODE;                                     // ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // długosc słowa, DLAB = 1
   U0DLL   = ((15000000/16)/uiBaudRate);                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // wlaczamy przerwanie przy odebraniu znaku

   // INT
   VICVectAddr2  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl2  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

/*******************/
#define TERMINATOR 0x0D
#define RECIEVER_SIZE 10
#define NULL 0

struct RecieverBuffer
{
char cData[RECIEVER_SIZE];						//przechowywanie lancucha znakowego
unsigned char ucCharCtr;							//iteracja po lancuchu
enum eRecieverStatus eStatus;					//status bufora
};

struct RecieverBuffer sRecieverBuffer;

void Reciever_PutCharacterToBuffer(char cCharacter)
{
	if(sRecieverBuffer.ucCharCtr >= RECIEVER_SIZE)
	{
		sRecieverBuffer.eStatus=OVERFLOW;
	}
	else if(cCharacter != TERMINATOR)
	{
		sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr]=cCharacter;
		sRecieverBuffer.ucCharCtr++;
	}
	else
	{
		sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr]=NULL;
		sRecieverBuffer.eStatus=READY;
		sRecieverBuffer.ucCharCtr=0;
	}
}

enum eRecieverStatus eReciever_GetStatus(void)
{
	return sRecieverBuffer.eStatus;
}

void Reciever_GetStringCopy(char * ucDestination)
{
	CopyString(sRecieverBuffer.cData, ucDestination);
	sRecieverBuffer.eStatus=EMPTY;
}


