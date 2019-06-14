#define RECIEVER_SIZE 10

enum eRecieverStatus {EMPTY, READY, OVERFLOW};

struct RecieverBuffer
{
char cData[RECIEVER_SIZE];						//przechowywanie lancucha znakowego
unsigned char ucCharCtr;							//iteracja po lancuchu
enum eRecieverStatus eStatus;					//status bufora
};

__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
enum eRecieverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char * ucDestination);
