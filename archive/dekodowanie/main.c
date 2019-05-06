#include <LPC21xx.H>
#include <stdio.h>
#include <stdlib.h>
#define NULL 0

enum Result { OK, ERROR };

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCharCounter;

	for (ucCharCounter = 0; pcSource[ucCharCounter] != NULL; ucCharCounter++)
  {
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
	}
	pcDestination[ucCharCounter] = NULL;
}


enum CompResult { DIFFERENT , EQUAL };

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

enum Result Testof_CopyString()
{
	char pcTestSource[] = "Test1";
	char pcTestDestination[6];
	
	CopyString(pcTestSource,pcTestDestination);
	if(eCompareString(pcTestSource,pcTestDestination)==EQUAL)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

enum Result Testof_eCompareString()
{
	char pcTest1[] = "Test1";
	char pcTest2[] = "Test2";
	
	if((eCompareString(pcTest1,pcTest2)==EQUAL)||(eCompareString(pcTest1,pcTest1)==DIFFERENT))
	{
		return ERROR;
	}
	else
	{
		return OK;
	}
}

void AppendString(char pcSourceStr[],char pcDestinationStr[])
{
	unsigned char ucCharCounter;

	for(ucCharCounter = 0; pcDestinationStr[ucCharCounter] != NULL; ucCharCounter++){}
	CopyString(pcSourceStr, pcDestinationStr+ucCharCounter);
}

enum Result Testof_AppendString()
{
	char pcTestSource[] = "1";
	char pcTestDestination[] = "Test";
	char pcTestResult[] = "Test1";
	
	AppendString(pcTestSource,pcTestDestination);
	if(eCompareString(pcTestDestination,pcTestResult)==EQUAL)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
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

enum Result Testof_ReplaceCharactersInString()
{
	char pcTest[] = "Test1";
	char pcTestResult[] = "Test2";
	
	ReplaceCharactersInString(pcTest,'1','2');
	if(eCompareString(pcTest,pcTestResult)==EQUAL)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

//===========================================================================================================
//===========================================================================================================
//===========================================================================================================

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

enum Result Testof_UIntToHexStr()
{
	unsigned int uiTestValue = 60;
	char pcTestDestination[6];
	char pcTestResult[] = "0x003C";
	
	UIntToHexStr(uiTestValue, pcTestDestination);
	if(eCompareString(pcTestDestination,pcTestResult)==EQUAL)
	{
		return OK;
	}
	else
	{
		return ERROR;
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

enum Result Testof_eHexStringToUInt()
{
	char pcTestString[] = "0x003C";
	unsigned int uiTestDestination;
	
	eHexStringToUInt(pcTestString, &uiTestDestination);
	if(uiTestDestination == 60)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucEndPointer;

	for(ucEndPointer=0; pcDestinationStr[ucEndPointer]!=NULL; ucEndPointer++){}
	UIntToHexStr(uiValue,&pcDestinationStr[ucEndPointer]);
}

enum Result Testof_AppendUIntToString()
{
	char pcTestString[10] = "Test";
	unsigned int uiTestValue = 60;
	char pcTestResult[] = "Test0x003C";
	
	AppendUIntToString(uiTestValue, pcTestString);
	if(eCompareString(pcTestString,pcTestResult)==EQUAL)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

//===========================================================================================================
//===========================================================================================================
//===========================================================================================================

enum KeywordCode { LD, ST, RST};
enum TokenType { KEYWORD, NUMBER, STRING};

union TokenValue
{
	enum KeywordCode eKeyword; // jezeli KEYWORD
	unsigned int uiNumber; // jezeli NUMBER
  char *pcString; // jezeli STRING
};

struct Token
{
  enum TokenType eType; // KEYWORD, NUMBER, STRING
  union TokenValue uValue; // enum, unsigned int, char*
};

#define MAX_TOKEN_NR 3
struct Token asToken[MAX_TOKEN_NR];

#define MAX_KEYWORD_STRING_LTH 10

struct Keyword
{
  enum KeywordCode eCode;
  char cString[MAX_KEYWORD_STRING_LTH + 1];
};

unsigned char ucTokenNr;

#define MAX_KEYWORD_NR 3
struct Keyword asKeywordList[MAX_KEYWORD_NR]=
{
  {RST,"reset"},
  {LD, "load" },
  {ST, "store"}
};

unsigned char ucFindTokensInString(char *pcString)
{
  unsigned char ucTokenPointer;
  unsigned char ucTokenCounter=0;
  char cCurrentChar;
  enum State {TOKEN, DELIMITER};
  enum State eState = DELIMITER;

  for(ucTokenPointer=0 ;; ucTokenPointer++)
  {
		cCurrentChar = pcString[ucTokenPointer];
    switch(eState)
    {
			case DELIMITER:
				if(cCurrentChar == NULL)
        {
					return ucTokenCounter;
				}
        else if(cCurrentChar != ' ')
        {
					eState = TOKEN;
          asToken[ucTokenCounter].uValue.pcString = pcString + ucTokenPointer;
          ucTokenCounter++;
        }
        break;
			case TOKEN:
        if(cCurrentChar == NULL)
        {
					return ucTokenCounter;
        }
        else if(ucTokenCounter == MAX_TOKEN_NR)
        {
					return ucTokenCounter;
        }
        else if(cCurrentChar == ' ')
        {
					eState = DELIMITER;
        }
        break;
		}
  }
}

enum Result Testof_ucFindTokensInString()
{
	char test1[] = "        ";
	char test2[] = " token1 token2";
	char test3[] = "token1   token2";
	
	if((ucFindTokensInString(test1)==0)&&(ucFindTokensInString(test2)==2)&&(ucFindTokensInString(test3)==2))
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode)
{
	unsigned char ucKeywordIndex;

  for(ucKeywordIndex=0 ; ucKeywordIndex < MAX_KEYWORD_NR ; ucKeywordIndex++)
  {
		if(eCompareString(pcStr, asKeywordList[ucKeywordIndex].cString) == EQUAL)
    {
			*peKeywordCode = asKeywordList[ucKeywordIndex].eCode;
			return OK;
    }
  }
  return ERROR;
}

enum Result Testof_eStringToKeyword()
{
	char test[] = "reset";
	enum KeywordCode eTestKeywordCode;
	eStringToKeyword(test, &eTestKeywordCode);
	if(eTestKeywordCode == RST)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

void DecodeTokens(void)
{
  unsigned char ucCurrentToken;
  unsigned int uiHexValue;
  enum KeywordCode Keyword;
  struct Token* pasValue;

  for(ucCurrentToken=0 ;ucCurrentToken < ucTokenNr ; ucCurrentToken++)
  {
		pasValue = &asToken[ucCurrentToken];
    if(eStringToKeyword(pasValue->uValue.pcString, &Keyword) == OK)
			{
				pasValue->eType = KEYWORD;
				pasValue->uValue.eKeyword = Keyword;
      }
      else if(eHexStringToUInt(pasValue->uValue.pcString, &uiHexValue) == OK)
      {
        pasValue->eType = NUMBER;
        pasValue->uValue.uiNumber = uiHexValue;
      }
      else
      {
				pasValue->eType = STRING;
				//pasValue->uValue.pcString = pcStr;
      }
  }
}

enum Result Testof_DecodeTokens()
{
	char pcTestMsg1[]="load 0x3C token1";
	
	ucTokenNr=ucFindTokensInString(pcTestMsg1);
	ReplaceCharactersInString(pcTestMsg1,' ',NULL);
  DecodeTokens();
	if((asToken[0].eType != KEYWORD)||(asToken[0].uValue.eKeyword != LD))
	{
		return ERROR;
	}
	if((asToken[1].eType != NUMBER)||(asToken[1].uValue.uiNumber != 60))
	{
		return ERROR;
	}
	if((asToken[2].eType != STRING)||(eCompareString(asToken[2].uValue.pcString, "token1")==DIFFERENT))
	{
		return ERROR;
	}
	return OK;
}

void DecodeMsg(char *pcString)
{   
  ucTokenNr=ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ',NULL);
  DecodeTokens();
}

enum Result Testof_DecodeMsg()
{
	char pcTestMsg1[]="load 0x3C token1";
	
	DecodeMsg(pcTestMsg1);
	if((asToken[0].eType != KEYWORD)||(asToken[0].uValue.eKeyword != LD))
	{
		return ERROR;
	}
	if((asToken[1].eType != NUMBER)||(asToken[1].uValue.uiNumber != 60))
	{
		return ERROR;
	}
	if((asToken[2].eType != STRING)||(eCompareString(asToken[2].uValue.pcString, "token1")==DIFFERENT))
	{
		return ERROR;
	}
	return OK;
}

int main()
{
	char pcKomunikat[]="        ";
	char pcKomunikat2[]="load 0x3C token1";
	char pcKomunikat3[]="store token1 0x04C 0x3";
	DecodeMsg(pcKomunikat);
	DecodeMsg(pcKomunikat2);
	DecodeMsg(pcKomunikat3);
	/*enum Result TestResult;
	TestResult = Testof_CopyString();
	TestResult = Testof_eCompareString();
	TestResult = Testof_AppendString();
	TestResult = Testof_ReplaceCharactersInString();
	TestResult = Testof_UIntToHexStr();
	TestResult = Testof_eHexStringToUInt();
	TestResult = Testof_AppendUIntToString();
	TestResult = Testof_ucFindTokensInString();
	TestResult = Testof_eStringToKeyword();
	TestResult = Testof_DecodeTokens();*/
	//return 0;
}
