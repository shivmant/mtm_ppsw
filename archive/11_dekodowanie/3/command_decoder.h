#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
#define MAX_TOKEN_NR 3

enum KeywordCode { CLB, GOTO};
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

struct Keyword
{
  enum KeywordCode eCode;
  char cString[MAX_KEYWORD_STRING_LTH + 1];
};

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
