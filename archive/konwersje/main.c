#define NULL 0

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

enum Result { OK, ERROR };

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

char cHexStr1[] = "0xC1";
char cHexStr2[] = "0x00C1";
char cHexStr3[] = "0x00G1";
char cHexStr4[] = "0x00C12";
unsigned int uiDecValue1,uiDecValue2,uiDecValue3,uiDecValue4;
enum Result Result1, Result2, Result3, Result4;

int main()
{
	Result1 = eHexStringToUInt(cHexStr1, &uiDecValue1);
	Result2 = eHexStringToUInt(cHexStr2, &uiDecValue2);
	Result3 = eHexStringToUInt(cHexStr3, &uiDecValue3);
	Result4 = eHexStringToUInt(cHexStr4, &uiDecValue4);
}
