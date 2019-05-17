/*
 * ciLisp Project
 * RoboticRice
 * Task 6
 * In-Progress: 05/06/2019
 */

#ifndef __cilisp_h_
#define __cilisp_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "ciLispParser.h"

int yyparse(void);

int yylex(void);

void yyerror(char *);

typedef enum oper { // must be in sync with funcs in resolveFunc()
    NEG_OPER, // 0
    ABS_OPER, // 1
    EXP_OPER, // 2
    SQRT_OPER, // 3
    ADD_OPER, // 4
    SUB_OPER, // 5
    MULT_OPER, // 6
    DIV_OPER, // 7
    REMAINDER_OPER, // 8
    LOG_OPER, // 9
    POW_OPER, // 10
    MAX_OPER, // 11
    MIN_OPER, // 12
    EXP2_OPER, // 13
    CBRT_OPER, // 14
    HYPOT_OPER, // 15
    PRINT_OPER, //16
    RAND_OPER, //17
    READ_OPER, //18
    EQUAL_OPER, //19
    SMALL_OPER, //20
    LARGE_OPER, //21
    CUSTOM_FUNC=255
} OPER_TYPE;

OPER_TYPE resolveFunc(char *);

typedef enum {
    NUM_TYPE, //0
    FUNC_TYPE, //1
    SYMBOL_TYPE, //2
    CONDIT_TYPE //3
} AST_NODE_TYPE;

typedef struct symbol_table_node {
    char *ident;
    struct ast_node *val;
    struct symbol_table_node *next;
} SYMBOL_TABLE_NODE;

typedef enum {
    NAN_TYPE = -1,
    REAL_TYPE,  //0
    INT_TYPE    //1
}DATA_TYPE;

DATA_TYPE resolveType(char *);

typedef struct {
    DATA_TYPE type;
    double val;
}RETURN_VALUE;

typedef struct {
    //double value; //removed for part 3
    RETURN_VALUE retVal;
} NUMBER_AST_NODE;

typedef struct {
    char *name;
    struct ast_node *opList;
} FUNCTION_AST_NODE;

typedef struct {
    struct ast_node *cond;
    struct ast_node *zero;
    struct ast_node *nonzero;
} COND_AST_NODE;

typedef struct symbol_ast_node {
    char *name;
} SYMBOL_AST_NODE;

typedef struct ast_node {
    AST_NODE_TYPE type;
    SYMBOL_TABLE_NODE *symbolTable; //the local most scope of all defined variables
    struct ast_node *parent; //the next more global scope from current local scope
    union {
        NUMBER_AST_NODE number;
        FUNCTION_AST_NODE function;
        COND_AST_NODE condition;
        SYMBOL_AST_NODE symbol;
    } data;
    struct ast_node *next; //used for the linked list of parameters passed
} AST_NODE;

AST_NODE *number(double value, DATA_TYPE dtype);

AST_NODE *function(char *funcName, AST_NODE *opList);

AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbolTable, AST_NODE *s_expr);

AST_NODE *setConditions(AST_NODE *condition, AST_NODE *nonZero, AST_NODE *zero);

AST_NODE *symbol(char *name);

SYMBOL_TABLE_NODE *createSymbol(char *name, AST_NODE *val, DATA_TYPE dtype);

SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol);

SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol);

SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node);

void freeNode(AST_NODE *p);

RETURN_VALUE eval(AST_NODE *ast);

#endif
