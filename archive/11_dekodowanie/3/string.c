#include "string.h"
#define NULL 0

void CopyString(char pcSource[], char pcDestination[])
{

	unsigned char ucCharCounter;

	for (ucCharCounter = 0; pcSource[ucCharCounter] != NULL; ucCharCounter++)
    {
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
	}
	pcDestination[ucCharCounter] = NULL;
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{

	unsigned char ucCharCounter;

	for(ucCharCounter = 0; pcStr1[ucCharCounter] == pcStr2[ucCharCounter]; ucCharCounter++)
	{
		if( pcStr1[ucCharCounter] == NULL)
		{
		return EQUAL;
		}
	}
	return DIFFERENT;
}

void AppendString (char pcSourceStr[],char pcDestinationStr[])
{

	unsigned char ucCharCounter;

	for(ucCharCounter = 0; pcDestinationStr[ucCharCounter] != NULL; ucCharCounter++){}
	CopyString(pcSourceStr, pcDestinationStr+ucCharCounter);
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar)
{

	unsigned char ucCharCounter;

	for(ucCharCounter = 0; pcString[ucCharCounter] != NULL; ucCharCounter++)
	{
		if(pcString[ucCharCounter]==cOldChar)
		{
			pcString[ucCharCounter]=cNewChar;
		}
	}
}

void UIntToHexStr(unsigned int uiValue, char pcStr[])
{
	unsigned char ucNibbleCounter;
	unsigned char ucCurrentNibble;
	
	pcStr[0] = '0';
  pcStr[1] = 'x';
  pcStr[6] = NULL;
	for(ucNibbleCounter=0; ucNibbleCounter<4; ucNibbleCounter++)
  {
		ucCurrentNibble=(uiValue >> (ucNibbleCounter*4)) & 0x0F;
		if(ucCurrentNibble < 10)
		{
			pcStr[5-ucNibbleCounter] = '0' + ucCurrentNibble;
		}
		else
		{
			pcStr[5-ucNibbleCounter] = 'A' + (ucCurrentNibble-10);
		}
	}
}

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{

  unsigned char ucCharCounter;

	if((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL))
  {
		return ERROR;
  }
  *puiValue = 0;
  for(ucCharCounter=2; pcStr[ucCharCounter] != NULL; ucCharCounter++)
  {
		if(ucCharCounter == 6)
    {
			return ERROR;
    }
    *puiValue = *puiValue << 4;
    if((pcStr[ucCharCounter] >= 'A') && (pcStr[ucCharCounter] <= 'F'))
    {
			*puiValue = *puiValue | (pcStr[ucCharCounter] - 'A' + 10);
    }
		else if((pcStr[ucCharCounter] >= '0') && (pcStr[ucCharCounter] <= '9'))
    {
			*puiValue = *puiValue | (pcStr[ucCharCounter] - '0');
    }
		else
		{
			return ERROR;
		}
	}
	return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{

	unsigned char ucEndPointer;

	for(ucEndPointer=0; pcDestinationStr[ucEndPointer]!=NULL; ucEndPointer++){}
	UIntToHexStr(uiValue,&pcDestinationStr[ucEndPointer]);
}
