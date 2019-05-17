/**
 * Name: RoboticRice
 * Lab: 4 Scanner
 * Date: 02/20/2019
 *
 * Modified to use scannerNClass instead of scannerAdHoc
 * Also added lines 29 & 39 to include file input for stdin
 *
**/

//
//  main.c (driver for a scanner test)
//
//  Created by Bieszczad, A.J. on 9/20/17.
//  Copyright (c) 2017 CSUCI. All rights reserved.
//
//  ASSUMES: Lecture 1, 2, 3, 4

#include <unistd.h>
#include "scanner.h"

int main(int argc, char **argv)
{
    freopen(argv[1], "r", stdin);

    TOKEN *token = NULL;
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                         "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};
    printf("\n");
    while ((token = scannerNClass()) != NULL)
    {
        if ( token->strVal == NULL)
            printf("{%s}\n", token2str[token->type]);
        else
            printf("{%s, %s}\n", token2str[token->type], token->strVal);
        freeToken(&token);
        fflush(stdout);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}