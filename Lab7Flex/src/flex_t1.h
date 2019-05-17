/**
* Name: RoboticRice
* Lab: Lab 7 Flex
* Date: 03/13/209
**/

#ifndef __flex_t1_h_
#define __flex_t1_h_

#include <stdio.h>

typedef enum {
    IF_TOKEN = 258, // since Bison will start token at that number
    THEN_TOKEN,
    DO_TOKEN,
    WHILE_TOKEN,
    PRINT_TOKEN,
    NUMBER_TOKEN,
    ID_TOKEN,
    LPARAN_TOKEN,
    RPARAN_TOKEN,
    ASSIGN_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    DIV_TOKEN,
    MULT_TOKEN,
    MOD_TOKEN,
    SEMI_TOKEN,
    WS_TOKEN
    } TOKEN;

int yylex(void);
void yyerror(char *s);

#endif
