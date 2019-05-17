#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

typedef enum
{
    IDENTIFIER_NODE = 1,
    NUMBER_NODE,
    EXPR_NODE,
    TERM_NODE,
    ASSIGN_STMT_NODE,
    REPEAT_STMT_NODE,
    PRINT_STMT_NODE,
    FACTOR_NODE,
    PROGRAM_NODE,
    STATEMENT_NODE
} NODE_TYPE;

typedef struct node
{
    NODE_TYPE type;
    union
    {
        char identifier[128];
        double number;
        char op;
        //char addOp;
        //char multOp;
    } data;
    struct node *leftNode;
    struct node *rightNode;
} NODE;

NODE *program();

NODE *statement();

NODE *assignStmt(TOKEN **currToken);

NODE *repeatStmt(TOKEN **currToken);

NODE *printStmt(TOKEN **currToken);

NODE *expr(TOKEN **currToken);

NODE *term(TOKEN **currToken);

NODE *factor(TOKEN **currToken);

NODE *id(TOKEN **currToken);

NODE *number(TOKEN **currToken);

TOKEN *getNextToken(TOKEN **currToken);

void error(char *errorMsg);

#endif