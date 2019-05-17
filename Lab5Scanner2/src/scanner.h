/**
 * Name: RoboticRice
 * Lab: 5 Scanner 2
 * Date: 03/05/2019
 * *Submission V2
**/
// Lab5
//  scanner.h
//

#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum
{
    INVALID_TOKEN = 0,
    NUMBER_TOKEN, //1
    IDENT_TOKEN,  //2
    ASSIGNMENT,   //3
    SEMICOLON,    //4
    LPAREN,       //5
    RPAREN,       //6
    PLUS,         //7
    MINUS,        //8
    MULT,         //9
    DIV,          //10
    MOD,          //11
    REPEAT,
    PRINT,
    END_OF_INPUT_TOKEN
} TOKEN_TYPE;

typedef struct token
{
    TOKEN_TYPE type;
    char *strVal;
} TOKEN;

typedef struct
{
    int numberOfStates;
    int numberOfClasses;
    char **inputSymbolClasses; //array of character classes and their values (malloc char ptr per class) //replace "/n" with newline char with char size 1 =/= 2 //strsep()? strtok()?
    char **table;
} TRANS_TABLE_TYPE;

TRANS_TABLE_TYPE *scanInit();
void updateTypeIfKeyword(TOKEN *token);
int findIndexToClass(TRANS_TABLE_TYPE *transitionTable, char c);
TOKEN* scanner(TRANS_TABLE_TYPE *outputTable);

void ungetToken(TOKEN **);
void freeToken(TOKEN **);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256

#endif