enum KeywordCode { CLB, LFT, RGT};
enum TokenType { KEYWORD, NUMBER, STRING};

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
