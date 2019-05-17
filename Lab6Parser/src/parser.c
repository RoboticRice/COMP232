/**
* Name: RoboticRice
* Lab: Lab 6 Parser
* Date: 03/06/2019
**/

#include "parser.h"

TOKEN *getNextToken(TOKEN **token)
{
    freeToken(token);
    return scannerAdHoc();
}

NODE *program()
{
    NODE *node = malloc(sizeof(NODE));
    node->type = PROGRAM_NODE;
    node->leftNode = statement();
    if (node->leftNode != NULL)
        node->rightNode = program();
    else
        return NULL;
    return node;
}

NODE *statement()
{
    NODE *node = malloc(sizeof(NODE));
    node->type = STATEMENT_NODE;
    TOKEN **currentToken = malloc(sizeof(TOKEN*));
    *currentToken = getNextToken(NULL);
    switch ((*currentToken)->type)
    {
        case IDENT_TOKEN:
            node->leftNode = assignStmt(currentToken);
            break;
        case REPEAT_TOKEN:
            node->leftNode = repeatStmt(currentToken);
            break;
        case PRINT_TOKEN:
            node->leftNode = printStmt(currentToken);
            break;
        case END_OF_INPUT_TOKEN:
            return NULL;
        default:
            error("Expected <Ident>, <repeat>, <print>, or <EOF>. Found something else...");
            break;//5% change scanner to return end of input token
    }
    return node;
}

NODE *assignStmt(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = ASSIGN_STMT_NODE;
    //we know assgnStmt starts with an ident
    node->leftNode = id(currToken);
    *currToken = getNextToken(currToken);
    if ((*currToken)->type == ASSIGNMENT_TOKEN) //if "=" is after ident
    {
        node->rightNode = expr(currToken);
        //no need to store = in data since it is implied
        *currToken = getNextToken(currToken);
        if ((*currToken)->type != SEMICOLON_TOKEN) //if statement does not end with ";"
            error("Expected <;>");
    } else
        error("Expected <=>");
    return node;
}

NODE *repeatStmt(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = REPEAT_STMT_NODE;
    *currToken = getNextToken(currToken);
    if ((*currToken)->type == LPAREN_TOKEN) //if "(" is after repeat
    {
        node->leftNode = expr(currToken);
        *currToken = getNextToken(currToken);
        if ((*currToken)->type == RPAREN_TOKEN) //if expr is followed by ")"
        {
            node->rightNode = statement();
            *currToken = getNextToken(currToken);
            if ((*currToken)->type != SEMICOLON_TOKEN) //if repeat does not end with ";" (stmt also ends in ;, so it will look like ";;")
                error("Expected <;>");
        } else
            error("Expected <)>");
    } else
        error("Expected <(>");
    return node;
}

NODE *printStmt(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = PRINT_STMT_NODE;
    node->leftNode = expr(currToken); //immediately try an expr, since there's nothing in-between print and expr
    *currToken = getNextToken(currToken);
    if ((*currToken)->type != SEMICOLON_TOKEN) //if print does not end with ";"
        error("Expected <;>");
    return node;
}

NODE *expr(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = EXPR_NODE;
    node->leftNode = term(currToken);
    *currToken = getNextToken(currToken);
    switch ((*currToken)->type)
    {
        case PLUS_TOKEN:
            node->data.op = '+';
            node->rightNode = expr(currToken);
            break;
        case MINUS_TOKEN:
            node->data.op = '-';
            node->rightNode = expr(currToken);
            break;
        default:
            ungetToken(currToken);
            break;
    }
    return node;
}

NODE *term(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = TERM_NODE;
    node->leftNode = factor(currToken);
    *currToken = getNextToken(currToken);
    switch ((*currToken)->type)
    {
        case MULT_TOKEN:
            node->data.op = '*';
            node->rightNode = expr(currToken);
            break;
        case DIV_TOKEN:
            node->data.op = '/';
            node->rightNode = expr(currToken);
            break;
        case MOD_TOKEN:
            node->data.op = '%';
            node->rightNode = expr(currToken);
            break;
        default:
            ungetToken(currToken);
            break;
    }
    return node;
}

NODE *factor(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = FACTOR_NODE;
    *currToken = getNextToken(currToken);
    switch ((*currToken)->type)
    {
        case MINUS_TOKEN:
            //node->data.op = '-'; not required, as the only time a factor will DIRECTLY child a factor is if there is a minus token
            node->leftNode = factor(currToken);
            break;
        case IDENT_TOKEN:
            node->leftNode = id(currToken);
            break;
        case NUMBER_TOKEN:
            node->leftNode = number(currToken);
            break;
        case LPAREN_TOKEN:
            node->leftNode = expr(currToken);
            *currToken = getNextToken(currToken);
            if ((*currToken)->type != RPAREN_TOKEN) //if (factor) does not end with ")"
                error("Expected <)>");
            break;
        default:
            error("Expected <->, <Ident>, <Number>, or <(>");
            break;
    }
    return node;
}

NODE *id(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = IDENTIFIER_NODE;
    //Terminal!
    strcpy(node->data.identifier, (*currToken)->strVal);
    freeToken(currToken);
    return node;
}

NODE *number(TOKEN **currToken)
{
    NODE *node = malloc(sizeof(NODE));
    node->type = NUMBER_NODE;
    //Terminal!
    node->data.number = strtod((*currToken)->strVal, NULL);
    freeToken(currToken);
    return node;
}

void error(char *errorMessage)
{
    printf("PARSING ERROR: %s\nExiting...\n", errorMessage);
    exit(1);
}
