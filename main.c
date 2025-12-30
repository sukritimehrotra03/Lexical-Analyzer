#include <stdio.h>
#include <string.h>
#include "lexer.h"

int i;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <.c file>\n", argv[0]);
        return FAILURE;
    }

    char ext_check[] = ".c";

    int j = 0, k = 0, flag = 0;
    char str[50];
    // Extract the file extension from the argument
    while (argv[1][j] != '\0')
    {
        if (argv[1][j] == '.')
        {
            flag = 1;
        }

        if (flag == 1)
        {
            str[k++] = argv[1][j];
        }
        j++;
    }
    // NULL-terminate the string
    str[k] = '\0';

    // Check if the file has the correct extension
    if (strcmp(str, ext_check) != 0)
    {
        printf("ERROR: %s does not have correct file extension.\n", argv[1]);
        return FAILURE;
    }

    FILE *fp;
    if (initializeLexer(argv[1], &fp) == FAILURE)
    {
        return FAILURE;
    }
    else
    {
        printf("Open    : %s : Success\n", argv[1]);
    }

    Token token;
    char line[256];
    printf("Parsing : %s : Started\n\n", argv[1]);
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        i = 0; // Reset index for each line

        while ((token = getNextToken(line)).type != UNKNOWN)
        {
            printf("Token: %-20sType: %-15s\n", token.lexeme, result[token.type]);
        }
    }
    printf("Parsing : %s : Done\n", argv[1]);

    return 0;
}
