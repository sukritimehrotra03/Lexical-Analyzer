#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

extern int i;

static const char *keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct"};

static const char *operators = "+-*/%=!<>|&";
static const char *specialCharacters = ",;{}()[]";

int initializeLexer(const char *filename, FILE **fp)
{
    *fp = fopen(filename, "r");

    if (*fp == NULL)
    {
        perror(filename);
        return FAILURE;
    }
    return SUCCESS;
}

Token getNextToken(const char *arr)
{
    Token tk;

    if (arr[i] == '\0')
    {
        tk.type = UNKNOWN;
        return tk;
    }

    while(arr[i] == ' ')
    {
        i++;
    }

    int j = 0;
    char word[50];

    if (isalpha(arr[i]))
    {
        while (isalnum(arr[i]))
        {
            word[j++] = arr[i++];
        }
    }
    else if (isdigit(arr[i]))
    {
        while (isdigit(arr[i]))
        {
            word[j++] = arr[i++];
        }
    }
    else if (arr[i] == '"' || arr[i] == '\'')
    {
        char quote = arr[i];
        word[j++] = arr[i++];
        while (arr[i] != quote && arr[i] != '\0')
        {
            word[j++] = arr[i++];
        }
        if (arr[i] == quote)
        {
            word[j++] = arr[i++];
        }
    }
    else
    {
        if (arr[i] != ' ')
        {
            word[j++] = arr[i++];
        }
        else
        {
            i++;
        }
    }

    word[j] = '\0';

    strcpy(tk.lexeme, word);
    categorizeToken(&tk);
    return tk;
}

void categorizeToken(Token *token)
{
    if (isalpha(token->lexeme[0]))
    {
        if (isKeyword(token->lexeme) == SUCCESS)
        {
            token->type = KEYWORD;
        }
        else
        {
            token->type = IDENTIFIER;
        }
    }
    else if(strstr(token->lexeme, "#") != NULL)
    {
        token->type = PREPROCESSOR;
    }
    else if (isOperator(token->lexeme) == SUCCESS)
    {
        token->type = OPERATOR;
    }
    else if (isSpecialCharacter(token->lexeme) == SUCCESS)
    {
        token->type = SPECIAL_CHARACTER;
    }
    else if (isConstant(token->lexeme) == SUCCESS)
    {
        token->type = CONSTANT;
    }
    else
    {
        token->type = UNKNOWN;
    }
}

int isKeyword(const char *str)
{
    for (int i = 0; i < MAX_KEYWORDS; i++)
    {
        if (strcmp(keywords[i], str) == 0)
        {
            return SUCCESS;
        }
    }
    return FAILURE;
}

int isOperator(const char *str)
{
    if (strstr(operators, str) != NULL)
    {
        return SUCCESS;
    }
    return FAILURE;
}

int isSpecialCharacter(const char *str)
{
    if (strstr(specialCharacters, str) != NULL)
    {
        return SUCCESS;
    }
    return FAILURE;
}

int isConstant(const char *str)
{
    int j = 0;
    if ((str[0] == '"' || str[0] == '\'') && (str[strlen(str) - 1] == '"' || str[strlen(str) - 1] == '\''))
    {
        return SUCCESS;
    }
    else
    {
        while (str[j] != '\0')
        {
            if (!isdigit(str[j]))
            {
                return FAILURE;
            }
            j++;
        }
        return SUCCESS;
    }
    return FAILURE;
}