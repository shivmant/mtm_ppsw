#include "command_decoder.h"
#include "string.h"

#define NULL 0

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
  {CLB,"callib"},
  {LFT, "left"  },
  {RGT, "right" }
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
      }
  }
}

void DecodeMsg(char *pcString)
{
  ucTokenNr=ucFindTokensInString(pcString);
  ReplaceCharactersInString(pcString,' ',NULL);
  DecodeTokens();
}
