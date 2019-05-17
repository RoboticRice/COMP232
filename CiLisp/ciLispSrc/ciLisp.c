/*
 * ciLisp Project
 * RoboticRice
 * Task 1
 * Completed: 05/01/2019
 */

#include "ciLisp.h"

void yyerror(char *s) {
    fprintf(stderr, "\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

//
// find out which function it is
//

char *func[] = {"neg",
                "abs",
                "exp",
                "sqrt",
                "add",
                "sub",
                "mult",
                "div",
                "remainder",
                "log",
                "pow",
                "max",
                "min",
//                "exp2",
//                "cbrt",
//                "hypot",
//                "print",
//        //TODO TASK 6:
//                "rand", //generate a random double, by any means
//                "read", //scanf from user to get value
//                "equal", //return T/F (0 or 1)
//                "smaller", //return T/F (0 or 1)
//                "larger", //return T/F (0 or 1)
                ""};

OPER_TYPE resolveFunc(char *funcName)
{
    int i = 0;
    while (func[i][0] != '\0')
    {
        if (strcmp(func[i], funcName) == 0)
            return i;

        i++;
    }
    return CUSTOM_FUNC;
}

//
// create a node for a number
//
AST_NODE *number(double value)
{
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value = value;

    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2)
{
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    p->data.function.op1 = op1;
    p->data.function.op2 = op2;

    return p;
}

//
// free a node
//
void freeNode(AST_NODE *p)
{
    if (!p)
        return;

    if (p->type == FUNC_TYPE)
    {
        free(p->data.function.name);
        freeNode(p->data.function.op1);
        freeNode(p->data.function.op2);
    }

    free(p);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
double eval(AST_NODE *p)
{
    if (!p)
        return NAN;

    double retVal = NAN;

    switch (p->type) {
        //case SYMBOL_TYPE:
        case NUM_TYPE:
            return p->data.number.value;
        case FUNC_TYPE:
            //TODO TASK 6: Check if at least one param is passed
            switch (resolveFunc(p->data.function.name)) {
                case NEG_OPER:
                    retVal = -1 * eval(p->data.function.op1);
                    break;
                case ABS_OPER:
                    retVal = fabs(eval(p->data.function.op1));
                    break;
                case EXP_OPER:
                    retVal = exp(eval(p->data.function.op1));
                    break;
                case SQRT_OPER:
                    retVal = sqrt(eval(p->data.function.op1));
                    break;
                case ADD_OPER:
                    retVal = eval(p->data.function.op1);
                    retVal += eval(p->data.function.op2);
                    break;
                case SUB_OPER:
                    retVal = eval(p->data.function.op1);
                    retVal -= eval(p->data.function.op2);
                    break;
                case MULT_OPER:
                    retVal = eval(p->data.function.op1);
                    retVal *= eval(p->data.function.op2);
                    break;
                case DIV_OPER:
                    retVal = eval(p->data.function.op2);
                    if (retVal == 0)
                        break; //returns NAN
                    retVal = eval(p->data.function.op1) / eval(p->data.function.op2);
                    break;
                case REMAINDER_OPER:
                    retVal = remainder(eval(p->data.function.op1), eval(p->data.function.op2));
                    break;
                case LOG_OPER:
                    ///DESIGN CHOICE: Only accept one varriable for log, and do the std log func
                    retVal = log(eval(p->data.function.op1));
                    break;
                case POW_OPER:
                    retVal = pow(eval(p->data.function.op1), eval(p->data.function.op2));
                    break;
                case MAX_OPER:
                    retVal = fmax(eval(p->data.function.op1), eval(p->data.function.op2));
                    break;
                case MIN_OPER:
                    retVal = fmin(eval(p->data.function.op1), eval(p->data.function.op2));
                    break;
                    //TODO TASK 4?
//                case EXP2_OPER:
//                case CBRT_OPER:
//                case HYPOT_OPER:
//                case PRINT_OPER:
                default: //CUSTOM_FUNC - not used?
                    break;
            }
    }

    return retVal;
}  

