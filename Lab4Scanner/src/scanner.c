/**
 * Name: RoboticRice
 * Lab: 4 Scanner
 * Date: 02/20/2019
**/

#include <ctype.h>
#include "scanner.h"

////NOT USED:
//TOKEN *ungottenToken = NULL; // used by parser
//
////
//// return token to the input, so it can be analyzed again
////
//void ungetToken(TOKEN **token)
//{
//    ungottenToken = *token;
//    *token = NULL;
//}

//
// clean up the token structure
//
void freeToken(TOKEN **token)
{
    if (token == NULL)
        return;

    if (*token == NULL)
        return;

    if ((*token)->strVal != NULL)
        free((*token)->strVal);

    free(*token);

    *token = NULL;
}

//
// check if a collected sequence of characters is a keyword
//
bool isKeyword(TOKEN *token, char *str)
{
    if (strcmp(str, "repeat") == 0)
        token->type = REPEAT_TOKEN;
    else if (strcmp(str, "print") == 0)
        token->type = PRINT_TOKEN;
    else
        return false;

    return true;
}

//
// scan input for a token using the nested class method
//
TOKEN *scannerNClass()
{
    // temporary buffer for collecting characters
    char tempString[BUF_SIZE];

    // acquire space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN; // assume that the token is invalid to start with
    token->strVal = NULL;

    // analyze the input character by character figuring out what kind of token they constitute
    char c;
    int i;
    int state = 1;
    c = getchar();
    while (c != EOF) //(token->type == INVALID_TOKEN) no longer needed. Only loops if token not set
    {
        switch (state){
            case 1: //default state
                switch (c){
                    case 'a'...'z': //c is a letter
                        state = 2;
                        break;
                    case '0'...'9': //c is a number
                        state = 3;
                        break;
                    case '=':
                        state = 4;
                        break;
                    case ';':
                        state = 5;
                        break;
                    case '(':
                        state = 6;
                        break;
                    case ')':
                        state = 7;
                        break;
                    case '+':
                        state = 8;
                        break;
                    case '-':
                        state = 9;
                        break;
                    case '*':
                        state = 10;
                        break;
                    case '/':
                        state = 11;
                        break;
                    case '%':
                        state = 12;
                        break;
                    case ' ': // skip whitespace
                    case '\t':
                    case '\n':
                        c = getchar(); //get new char input, then try again.
                        break;
                    default:
                        //Invalid input!
                        //token->type = INVALID_TOKEN; //<- already invalid, no need to re-assign
                        return token;
                }
                break;
            case 2: //[a...z], start of id/keyword loop
                i = 0;
                do
                {
                    tempString[i++] = c;
                    c = getchar();
                } while (c >= 'a' && c <= 'z');
                tempString[i] = '\0';
                ungetc(c, stdin); // the last character read is not a letter, so return it to the input stream
                if (!isKeyword(token, tempString))
                {
                    token->type = IDENT_TOKEN;
                    token->strVal = (char *) malloc(strlen(tempString) + 1);
                    strcpy(token->strVal, tempString);
                }
                break;
            case 3: //[0...9], start of number loop
                i = 0;
                do
                {
                    tempString[i++] = c;
                    c = getchar();
                } while (isdigit(c) != 0);//(c >= '0' && c <= '9');
                tempString[i] = '\0';
                ungetc(c, stdin);
                token->type = NUMBER_TOKEN;
                // this scanner saves each token as a string and
                // assumes that the parser will interpret it as needed
                token->strVal = (char *) malloc(strlen(tempString) + 1);
                strcpy(token->strVal, tempString);
                break;
            case 4: //=
                token->type = ASSIGNMENT_TOKEN;
                break;
            case 5: //;
                token->type = SEMICOLON_TOKEN;
                break;
            case 6: //(
                token->type = LPAREN_TOKEN;
                break;
            case 7: //)
                token->type = RPAREN_TOKEN;
                break;
            case 8: //+
                token->type = PLUS_TOKEN;
                break;
            case 9: //-
                token->type = MINUS_TOKEN;
                break;
            case 10: //*
                token->type = MULT_TOKEN;
                break;
            case 11: //[/]
                token->type = DIV_TOKEN;
                break;
            case 12: //%
                token->type = MOD_TOKEN;
                break;
        }
        if (token->type != INVALID_TOKEN){
            return token;
        }
    }
    //if (c == EOF) //always true
    //{
        free(token);
        return NULL;
    //}
    //return token;
}