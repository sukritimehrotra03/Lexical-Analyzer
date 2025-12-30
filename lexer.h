#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 20
#define MAX_TOKEN_SIZE 100
#define SUCCESS 0
#define FAILURE -1

typedef enum 
{
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    UNKNOWN,
    PREPROCESSOR
} TokenType;

static const char *result[7] = {"KEYWORD", "OPERATOR", "SPECIAL CHARACTER", "LITERAL", "IDENTIFIER", "UNKNOWN", "PREPROCESSOR DIRECTIVE"};

typedef struct 
{
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

int initializeLexer(const char* filename, FILE **fp);
Token getNextToken(const char *);
void categorizeToken(Token* token);
int isKeyword(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(const char* str);
int isConstant(const char* str);

#endif
