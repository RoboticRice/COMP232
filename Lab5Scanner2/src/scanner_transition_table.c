/**
 * Name: RoboticRice
 * Lab: 5 Scanner 2
 * Date: 03/05/2019
 * *Submission V2
**/
// Lab5
// scanner_transition_table.c
//
// Assumes lectures: 1, 2, 3, 4

#include "scanner.h"

TOKEN *ungottenToken = NULL; // may be used by parser in the next lab

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
void updateTypeIfKeyword(TOKEN *token)
{
// No need to Implement the function
}


TRANS_TABLE_TYPE *scanInit()
{
    TRANS_TABLE_TYPE *returnTable = malloc(sizeof(TRANS_TABLE_TYPE));
    char inputBuffer[BUF_SIZE] = {0};
    char inputChar; // *inputPtr, *e,

    int indexClass = 0, indexArray = 0;

    //assume safely formatted input
    scanf("%d %d \n", &returnTable->numberOfStates, &returnTable->numberOfClasses); //NOLINT
    returnTable->inputSymbolClasses = calloc((size_t)returnTable->numberOfClasses, sizeof(char*));
    while ((inputChar = getchar())&&(inputChar != '\n')) //assume the end of file comes after this line - aka, formatted correctly
    { //If I have to check each char to ensure I didn't get a delimiter char, then why would I use strsep, when I could just check each character without running strsep first, and get the same result
        switch (inputChar)
        {
            case ',':
                //switch to different class of characters!
                inputBuffer[indexArray] = '\0';
                returnTable->inputSymbolClasses[indexClass] = calloc(strlen(inputBuffer)+1, sizeof(char));//malloc(strlen(inputBuffer) * sizeof(char)+sizeof(char));
                stpcpy(returnTable->inputSymbolClasses[indexClass],inputBuffer);
                indexClass++;
                indexArray = 0;
                break;
            case '\\':
                inputBuffer[indexArray] = inputChar;
                inputChar = getchar();
                switch (inputChar)
                {
                    //case EOF:
                      //  break; //This should not happen in well formatted input
                    case 'n':
                        inputChar = '\n';
                        inputBuffer[indexArray] = inputChar; //overwrites the same position
                        break;
                    case 't':
                        inputChar = '\t';
                        inputBuffer[indexArray] = inputChar; //overwrites the same position
                        break;
                    default: //in the case that the '\' is what we are trying to use, move to next spot and accept both
                        indexArray++;
                        inputBuffer[indexArray] = inputChar;
                        break;
                }
                indexArray++;
                break;
            default:
                inputBuffer[indexArray] = inputChar;
                indexArray++;
                break;
        }
    }
    if (inputBuffer[0] != '\0') //assume correct formatting of input, allow the last section of char before the newline to be a class
    { //as long as there is content after the last comma and before the newline
        inputBuffer[indexArray] = '\0';
        returnTable->inputSymbolClasses[indexClass] = calloc(strlen(inputBuffer)+1, sizeof(char));//malloc(strlen(inputBuffer) * sizeof(char)+sizeof(char));
        stpcpy(returnTable->inputSymbolClasses[indexClass],inputBuffer);
    }

    //Reached the actual table now!
    returnTable->table = calloc((size_t)(returnTable->numberOfStates), sizeof(char*));
    for (int i = 0; i < returnTable->numberOfStates; i++) { //rows
        returnTable->table[i] = calloc((size_t)returnTable->numberOfClasses+2, sizeof(char));
        for (int j = 0; j < returnTable->numberOfClasses+2; j++) { //cols
            inputChar = (char)getchar(); //0-C & a - assume input file formatted correctly
            returnTable->table[i][j] = inputChar;//i=row,j=col
            getchar(); //used to get rid of junk whitespace
        }
    }
    return returnTable;
}

int findIndexToClass(TRANS_TABLE_TYPE *transitionTable, char c)
{
    int class;
    //put in char into table to find char class
    //find if char is in string, if not, go to next string in char class array, return index of char class
    for (class=0;class<transitionTable->numberOfClasses;class++){
        if (strchr(transitionTable->inputSymbolClasses[class],c)!=NULL)
            return class; //returns if found in any of the classes
    }
    return class;//transitionTable->numberOfClasses; <-same thing //returns if NOT found anywhere
}

TOKEN *scanner(TRANS_TABLE_TYPE *transitionTable)
{
    // acquire space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN; // assume that the token is invalid to start with
    token->strVal = NULL;

//while loop should be switch that is like 3 cases, index transition table with current state with char to find next thing
    int index = 0, cClass, row;//, state = 0;
    char c, state = 0;
    char inputBuffer[BUF_SIZE] = {0};
    while ((c = getchar())&&(c!=EOF))
    {
        cClass = findIndexToClass(transitionTable, c);
        row = state;
        state = transitionTable->table[row][cClass];
        switch (state) {
            case 'a':
                ungetc(c, stdin);
                token->type = transitionTable->table[row][transitionTable->numberOfClasses+1]; //the last col
                if (token->type <= '9') //number
                    token->type -= '0'; //int val 0-9
                else
                    token->type -= 55; //int val 10-12
                inputBuffer[index] = '\0';
                token->strVal = calloc((size_t)strlen(inputBuffer), sizeof(char));
                strcpy(token->strVal, inputBuffer);
                if (token->type == IDENT_TOKEN) { //check token type first, because it uses less overhead then checking strVal for EVERY token
                    if (strcmp(token->strVal, "print") == 0) {
                        token->type = PRINT;
                    } else if (strcmp(token->strVal, "repeat") == 0) {
                        token->type = REPEAT;
                    }
                }
                return token;
            case 'e':
                ungetc(c, stdin);
                puts("Error!");
                //token->type = INVALID_TOKEN; //not needed, invalid by default
                inputBuffer[index] = '\0';
                token->strVal = calloc((size_t)index+1, sizeof(char));
                strcpy(token->strVal, inputBuffer);
                return token;
            case 'A'...'C': //rather than re-write the contents of the default case in this case, I added an if so both A-C & 0-9 could use the default case without conflict
            case '0'...'9':
                if (state <= '9') //number
                    state -= '0'; //int val 0-9
                else
                    state -= 55; //int val 10-12
            default:
                switch (c){
                    case '\n':
                    case '\t':
                    case ' ':
                        //in the case of whitespace, do nothing (don't add it to buffer)
                        break;
                    default:
                        inputBuffer[index] = c;
                        index++;
                        break;
                }
                break;
        }
    }
    return NULL; //only reaches if at EOF or the assignment of getchar failed
}