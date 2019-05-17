/*
 * ciLisp Project
 * RoboticRice
 * Task 1
 * Completed: 05/01/2019
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
//    EXP2_OPER, // 13
//    CBRT_OPER, // 14
//    HYPOT_OPER, // 15
//    PRINT_OPER, //16
//    //TODO TASK 6:
//    RAND_OPER, //17
//    READ_OPER, //18
//    EQUAL_OPER, //19
//    SMALL_OPER, //20
//    LARGE_OPER, //21
    CUSTOM_FUNC=255
} OPER_TYPE;

OPER_TYPE resolveFunc(char *);

typedef enum {
    NUM_TYPE, FUNC_TYPE
} AST_NODE_TYPE;

typedef struct {
    double value;
} NUMBER_AST_NODE;

typedef struct {
    char *name;
    struct ast_node *op1;
    struct ast_node *op2;
} FUNCTION_AST_NODE;

typedef struct ast_node {
    AST_NODE_TYPE type;
    union {
        NUMBER_AST_NODE number;
        FUNCTION_AST_NODE function;
    } data;
} AST_NODE;

AST_NODE *number(double value);

AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2);

void freeNode(AST_NODE *p);

double eval(AST_NODE *ast);

#endif
