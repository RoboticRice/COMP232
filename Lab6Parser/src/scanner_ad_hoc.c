/**
* Name: RoboticRice
* Lab: Lab 6 Parser
* Date: 03/06/2019
**/

#include "scanner.h"

TOKEN *ungottenToken = NULL; // used by parser

//
// return token to the input, so it can be analyzed again
//
void ungetToken(TOKEN **token)
{
    ungottenToken = *token;
    *token = NULL;
}

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
// scan input for a token using the ad hoc method
//
TOKEN *scannerAdHoc()
{
    // reuse any token returned to the input
    if (ungottenToken != NULL)
    {
        TOKEN *tok = ungottenToken;
        ungottenToken = NULL;
        return tok;
    }

    // temporary buffer for collecting characters
    char tempString[BUF_SIZE];

    // acquire space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN; // assume that the token is invalid to start with
    token->strVal = NULL;

    // analyze the input character by character figuring out what kind of token they constitute
    char c;
    int i;
    while ((token->type == INVALID_TOKEN) && ((c = getchar()) != EOF))
    {
        switch (c)
        {
            case ' ': // skip whitespace
            case '\t':
            case '\n':
                break;
            case 'a'...'z': // c is a letter
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
                return token;
            case '0'...'9': // if c is a number
                i = 0;
                do
                {
                    tempString[i++] = c;
                    c = getchar();
                } while (c >= '0' && c <= '9');
                tempString[i] = '\0';
                ungetc(c, stdin);
                token->type = NUMBER_TOKEN;
                // this scanner saves each token as a string and
                // assumes that the parser will interpret it as needed
                token->strVal = (char *) malloc(strlen(tempString) + 1);
                strcpy(token->strVal, tempString);
                return token;
            default:
                // save the single character so the parser may distinguish operators if needed
                token->strVal = malloc(sizeof(char) + 1);
                token->strVal[0] = c;
                token->strVal[1] = '\0';
                switch (c)
                {
                    case '=':
                        token->type = ASSIGNMENT_TOKEN;
                        break;
                    case ';':
                        token->type = SEMICOLON_TOKEN;
                        break;
                    case '(':
                        token->type = LPAREN_TOKEN;
                        break;
                    case ')':
                        token->type = RPAREN_TOKEN;
                        break;
                    case '+':
                        token->type = PLUS_TOKEN;
                        break;
                    case '-':
                        token->type = MINUS_TOKEN;
                        break;
                    case '*':
                        token->type = MULT_TOKEN;
                        break;
                    case '/':
                        token->type = DIV_TOKEN;
                        break;
                    case '%':
                        token->type = MOD_TOKEN;
                        break;
                }
                return token;
        }
    }
    if (c == EOF)
    {
//        free(token);
//        return NULL;
        token->type = END_OF_INPUT_TOKEN;
    }
    return token;
}

