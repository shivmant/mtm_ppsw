#include <LPC21xx.H>
#include <stdio.h>
#include <stdlib.h>
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

int main()
{
  char slowo1[14]="slowo";
  char slowo2[14]="wyraz";
	//CopyString(slowo1, slowo2);
	//enum CompResult result = eCompareString(slowo1, slowo2);
  //AppendString(slowo1,slowo2);
	ReplaceCharactersInString(slowo1,'i','n');
	return 0;
}
