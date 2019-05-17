/**
* Name: RoboticRice
* Lab: Lab 6 Parser
* Date: 03/06/2019
**/

#include "eval.h"
#include "parser.h"

void printProgram(NODE *node)
{
    if (node == NULL)
        return;
    puts("=> START program");
    if (node->leftNode != NULL)
        printStatement(node->leftNode);
    if (node->rightNode != NULL)
        printProgram(node->rightNode);
    puts("=> END program");
    free(node);
}

void printStatement(NODE *node)
{
    puts("=> START statement");
    if (node->leftNode->type == ASSIGN_STMT_NODE)
        printAssignStmt(node->leftNode);
    else if (node->leftNode->type == REPEAT_STMT_NODE)
        printRepeatStmt(node->leftNode);
    else if (node->leftNode->type == PRINT_STMT_NODE)
        printPrintStmt(node->leftNode);
    puts("=> END statement");
    free(node);
}

void printAssignStmt(NODE *node)
{
    puts("=> START assignStmt");
    printId(node->leftNode);
    printExpr(node->rightNode);
    puts("=> END assignStmt");
    free(node);
}

void printRepeatStmt(NODE *node)
{
    puts("=> START repeatStmt");
    printExpr(node->leftNode);
    printStatement(node->rightNode);
    puts("=> END repeatStmt");
    free(node);
}

void printPrintStmt(NODE *node)
{
    puts("=> START printStmt");
    printExpr(node->leftNode);
    puts("=> END printStmt");
    free(node);
}

void printExpr(NODE *node)
{
    puts("=> START expr");
    printTerm(node->leftNode);
    if (node->rightNode != NULL) {
        printExpr(node->rightNode);
        printf("<%c>\n", node->data.op);
    }
    puts("=> END expr");
    free(node);
}

void printTerm(NODE *node)
{
    puts("=> START term");
    printFactor(node->leftNode);
    if (node->rightNode != NULL) {
        printExpr(node->rightNode);
        printf("<%c>\n", node->data.op);
    }
    puts("=> END term");
    free(node);
}

void printFactor(NODE *node)
{
    puts("=> START factor");
    switch (node->leftNode->type)
    {
        case FACTOR_NODE:
            printf("<->\n"); //explicitly defined, as there is only one option
            printFactor(node->leftNode);
            break;
        case IDENTIFIER_NODE:
            printId(node->leftNode);
            break;
        case NUMBER_NODE:
            printNumber(node->leftNode);
            break;
        case EXPR_NODE:
            printExpr(node->leftNode);
            break;
        default:
            error("This should never happen.");
            break;
    }
    puts("=> END factor");
    free(node);
}

void printId(NODE *node)
{
    puts("=> START ident");
    printf("<Ident> %s\n", node->data.identifier);
    free(node);
    puts("=> END ident");
}

void printNumber(NODE *node)
{
    puts("=> START number");
    printf("<Number> %lf\n", node->data.number);
    free(node);
    puts("=> END number");
}

