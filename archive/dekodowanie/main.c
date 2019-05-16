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

void Testof_CopyString()
{
	printf("CopyString\n\n");

	printf("Test 1 - ");
	//ta sama dlugosc
	char pcTestSource1[]="test1";
	char pcTestDestination1[]="aaaaa";
	CopyString(pcTestSource1, pcTestDestination1);
	if (eCompareString(pcTestSource1, pcTestDestination1)==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//pierwszy krotszy
	char pcTestSource2[]="test2";
	char pcTestDestination2[]="aaaaaaa";
	CopyString(pcTestSource2, pcTestDestination2);
	if (eCompareString(pcTestSource2, pcTestDestination2)==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 3 - ");
	//Source pusty
	char pcTestSource3[]="";
	char pcTestDestination3[]="aaaaa";
	CopyString(pcTestSource3, pcTestDestination3);
	if (eCompareString(pcTestSource3, pcTestDestination3)==EQUAL) printf("OK\n"); else printf("Error\n");
}

void TestOf_eCompareString()
{
	printf("eCompareString\n\n");

	printf("Test 1 - ");
	//takie same, ta sama dlugosc
	if (eCompareString("test1", "test1")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//rozne, ta sama dlugosc
	if (eCompareString("test1", "test2")==DIFFERENT) printf("OK\n"); else printf("Error\n");

	printf("Test 3 - ");
	///pierwszy pusty
	if (eCompareString("", "test2")==DIFFERENT) printf("OK\n"); else printf("Error\n");

	printf("Test 4 - ");
	//drugi pusty
	if (eCompareString("test1", "")==DIFFERENT) printf("OK\n"); else printf("Error\n");

	printf("Test 5 - ");
	///oba puste
	if (eCompareString("", "")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 6 - ");
	///drugi dluzszy
	if (eCompareString("test1", "test12")==DIFFERENT) printf("OK\n"); else printf("Error\n");
}

void AppendString(char pcSourceStr[],char pcDestinationStr[])
{
	unsigned char ucCharCounter;

	for(ucCharCounter = 0; pcDestinationStr[ucCharCounter] != NULL; ucCharCounter++){}
	CopyString(pcSourceStr, pcDestinationStr+ucCharCounter);
}

void TestOf_AppendString()
{
	printf("AppendString\n\n");

	printf("Test 1 - ");
	//dowolne
	char pcTestSource1[]="1";
	char pcTestDestination1[]="test";
	AppendString(pcTestSource1, pcTestDestination1);
	if (eCompareString(pcTestDestination1, "test1")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//source pusty
	char pcTestSource2[]="";
	char pcTestDestination2[]="test";
	AppendString(pcTestSource2, pcTestDestination2);
	if (eCompareString(pcTestDestination2, "test")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 3 - ");
	//destination pusty
	char pcTestSource3[]="test";
	char pcTestDestination3[]="";
	AppendString(pcTestSource3, pcTestDestination3);
	if (eCompareString(pcTestDestination3, "test")==EQUAL) printf("OK\n"); else printf("Error\n");
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

void TestOf_ReplaceCharactersInString()
{
	printf("ReplaceCharactersInString\n\n");

	printf("Test 1 - ");
	//rozne znaki
	char pcTestString1[]="test1";
	ReplaceCharactersInString(pcTestString1, '1', '2');
	if (eCompareString(pcTestString1, "test2")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//spacja na NULL
	char pcTestString2[]="komunikat testowy";
	ReplaceCharactersInString(pcTestString2, ' ', NULL);
	if (eCompareString(pcTestString2, "komunikat\0testowy")==EQUAL) printf("OK\n"); else printf("Error\n");
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

void TestOf_UIntToHexStr()
{
    char pcTestDestination[6];
	printf("UIntToHexStr\n\n");

	printf("Test 1 - ");
	//przypadek zerowy
	UIntToHexStr(60, pcTestDestination);
	if (eCompareString(pcTestDestination, "0x003C")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//krance przedzialow, 0,9,A,F
	UIntToHexStr(2479, pcTestDestination);
	if (eCompareString(pcTestDestination, "0x09AF")==EQUAL) printf("OK\n"); else printf("Error\n");
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

void TestOf_eHexStringToUInt()
{
	enum Result eReturnResult;
	unsigned int uiTestDestination;

	printf("eHexStringToUInt\n\n");

	printf("Test 1 - ");
	//krance przedzialow 0, 9, A, F
	eReturnResult = eHexStringToUInt("0x09AF", &uiTestDestination);
	if ((eReturnResult==OK)&&(uiTestDestination==2479)) printf("OK\n"); else printf("Error\n");
    printf("Test 2 - ");
	//mniej znakow
	eReturnResult = eHexStringToUInt("0x3C", &uiTestDestination);
	if ((eReturnResult==OK)&&(uiTestDestination==60)) printf("OK\n"); else printf("Error\n");
	printf("Test 3 - ");
	//za krotki
	eReturnResult = eHexStringToUInt("0x", &uiTestDestination);
	if (eReturnResult==ERROR) printf("OK\n"); else printf("Error\n");

	printf("Test 4 - ");
	//za dlugi
	eReturnResult = eHexStringToUInt("0x0003C", &uiTestDestination);
	if (eReturnResult==ERROR) printf("OK\n"); else printf("Error\n");

	printf("Test 5 - ");
	//poczatek rozny od 0x
	eReturnResult = eHexStringToUInt("003C", &uiTestDestination);
	if (eReturnResult==ERROR) printf("OK\n"); else printf("Error\n");
}


void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucEndPointer;

	for(ucEndPointer=0; pcDestinationStr[ucEndPointer]!=NULL; ucEndPointer++){}
	UIntToHexStr(uiValue,&pcDestinationStr[ucEndPointer]);
}

void TestOf_AppendUIntToString()
{
	printf("AppendUIntToString\n\n");

	printf("Test 1 - ");
	//niepusty string
	char pcTestString1[]="test";
	AppendUIntToString(60,pcTestString1);
	if (eCompareString(pcTestString1,"test0x003C")==EQUAL) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//pusty string
	char pcTestString2[]="";
	AppendUIntToString(60,pcTestString2);
	if (eCompareString(pcTestString2,"0x003C")==EQUAL) printf("OK\n"); else printf("Error\n");
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

void TestOf_ucFindTokensInString()
{
	unsigned char ucTokenNumber;

	printf("ucFindTokensInString\n\n");

	printf("Test 1 - ");
	//max liczba tokenów
	char pcTestString1[]="token1 token2 token3";
	ucTokenNumber=ucFindTokensInString(pcTestString1);
	if ((ucTokenNumber==3)&&(&pcTestString1[0]==asToken[0].uValue.pcString)&&(&pcTestString1[7]==asToken[1].uValue.pcString)&&(&pcTestString1[14]==asToken[2].uValue.pcString)) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//same delimitery
	char pcTestString2[]="    ";
	ucTokenNumber=ucFindTokensInString(pcTestString2);
	if (ucTokenNumber==0) printf("OK\n"); else printf("Error\n");

	printf("Test 3 - ");
	//delimitery na poczatku stringa, więcej niż jeden delimiter między tokenami, mniej tokenów niż max
	char pcTestString3[]="     token1     token2 ";
	ucTokenNumber=ucFindTokensInString(pcTestString3);
	if ((ucTokenNumber==2)&&(&pcTestString3[5]==asToken[0].uValue.pcString)&&(&pcTestString3[16]==asToken[1].uValue.pcString)) printf("OK\n"); else printf("Error\n");

	printf("Test 4 - ");
	//za dużo tokenów, (zwraca 3 i ustawia wskazniki na pierwsze 3)
	char pcTestString4[]="token1 token2 token3 token4";
	ucTokenNumber=ucFindTokensInString(pcTestString4);
	if ((ucTokenNumber==3)&&(&pcTestString4[0]==asToken[0].uValue.pcString)&&(&pcTestString4[7]==asToken[1].uValue.pcString)&&(&pcTestString4[14]==asToken[2].uValue.pcString)) printf("OK\n"); else printf("Error\n");
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

void TestOf_eStringToKeyword()
{
	enum KeywordCode eTokenCode;

	printf("eStringToKeyword\n\n");

	printf("Test 1 - ");
	//słowo kluczowe
	if ((eStringToKeyword("reset", &eTokenCode)==OK)&&(eTokenCode==RST)) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//brak słowa kluczowego
	if (eStringToKeyword("token1", &eTokenCode)==ERROR) printf("OK\n"); else printf("Error\n");
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
				//pasValue->uValue.pcString = pcStr[];
      }
  }
}

void TestOf_DecodeTokens()
{
	unsigned char ucTokenNumber;
	char pcTestToken1[]="load";
	char pcTestToken2[]="0x3C";
	char pcTestToken3[]="token1";
    asToken[0].uValue.pcString=&pcTestToken1[0];
    asToken[1].uValue.pcString=&pcTestToken2[0];
    asToken[2].uValue.pcString=&pcTestToken3[0];
    ucTokenNr=3;
	printf("DecodeTokens\n\n");

	printf("Test 1 - ");
	//keyword, liczba, string
	DecodeTokens();
	if ((asToken[0].eType==KEYWORD)&&(asToken[0].uValue.eKeyword==LD)&&(asToken[1].eType==NUMBER)&&(asToken[1].uValue.uiNumber==60)&&(asToken[2].eType==STRING)) printf("OK\n"); else printf("Error\n");
}

void DecodeMsg(char *pcString)
{
  ucTokenNr=ucFindTokensInString(pcString);
  ReplaceCharactersInString(pcString,' ',NULL);
  DecodeTokens();
}

void TestOf_DecodeMsg()
{
	char pcTestMsg[]="load 0x3C token1";

	printf("DecodeMsg\n\n");

	printf("Test 1 - ");
	//keyword, liczba, string
	DecodeMsg(pcTestMsg);
	if ((ucTokenNr==3)&&(asToken[0].eType==KEYWORD)&&(asToken[0].uValue.eKeyword==LD)&&(asToken[1].eType==NUMBER)&&(asToken[1].uValue.uiNumber==60)&&(asToken[2].eType==STRING)&&(asToken[2].uValue.pcString==&pcTestMsg[10])) printf("OK\n"); else printf("Error\n");
}

int main()
{
	Testof_CopyString();
    TestOf_eCompareString();
    TestOf_AppendString();
    TestOf_ReplaceCharactersInString();
    TestOf_UIntToHexStr();
    TestOf_eHexStringToUInt();
    TestOf_AppendUIntToString();
    TestOf_ucFindTokensInString();
    TestOf_eStringToKeyword();
    TestOf_DecodeTokens();
    TestOf_DecodeMsg();
	return 0;
}
