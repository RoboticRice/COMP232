/**
 * Name: RoboticRice
 * Lab: 5 Scanner 2
 * Date: 03/05/2019
 * *Submission V2
**/
// Lab5
//  main.c (driver for a scanner test)
//
//  ASSUMES: Lecture 1, 2, 3, 4

//Ident can have digits, as long as it has a letter to start
//digits can have a decimal or not, but must have digit first, and ay or may not have digit after
//puts(error), extra credit for invalid type with string of what is invalid
//ident or keyword ==
//use = not ;=


#include "scanner.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    TOKEN *token = NULL;
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                         "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};

    int savedstdin = dup(0); // save stdin file descriptor

    freopen(argv[1], "r", stdin); // possibly switch stdin to get the table from the file

    TRANS_TABLE_TYPE *transitionTable = scanInit();

    //dup2(savedstdin, 0);  // restore the original stdin, so we can read the input data from stdin

    freopen(argv[2], "r", stdin); //second input argument to find input filename

    while ((token = scanner(transitionTable)) != NULL)
    {
        if ( token->strVal == NULL)
            printf("{%s}\n", token2str[token->type]);
        else
            printf("{%s, %s}\n", token2str[token->type], token->strVal);
        freeToken(&token);
        fflush(stdout);
    }
    printf("\n");
}