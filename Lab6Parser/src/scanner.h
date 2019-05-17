#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    INVALID_TOKEN = 0,
    NUMBER_TOKEN,
    IDENT_TOKEN,
    ASSIGNMENT_TOKEN,
    SEMICOLON_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    MOD_TOKEN,
    REPEAT_TOKEN,
    PRINT_TOKEN,
    END_OF_INPUT_TOKEN
} TOKEN_TYPE;

typedef struct token
{
    TOKEN_TYPE type;
    char *strVal;
} TOKEN;

TOKEN *scannerAdHoc();

void ungetToken(TOKEN **);

void freeToken(TOKEN **);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256

#endif