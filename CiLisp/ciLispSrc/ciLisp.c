/*
 * ciLisp Project
 * RoboticRice
 * Task 5
 * In-Progress: 05/06/2019
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
                "exp2",
                "cbrt",
                "hypot",
                "print",
//        //TODO TASK 6:
//                "rand", //generate a random double, by any means
//                "read", //scanf from user to get value
//                "equal", //return T/F (0 or 1)
//                "smaller", //return T/F (0 or 1)
//                "larger", //return T/F (0 or 1)
                ""};

OPER_TYPE resolveFunc(char *funcName) {
    int i = 0;
    while (func[i][0] != '\0')
    {
        if (strcmp(func[i], funcName) == 0)
            return i;

        i++;
    }
    return CUSTOM_FUNC;
}

char *type[] = {"real",
                "integer",
                ""};

DATA_TYPE resolveType(char *typeName)
{
    int i = 0;
    while (type[i][0] != '\0')
    {
        if (strcmp(type[i], typeName) == 0)
            return i;

        i++;
    }
    return REAL_TYPE; //default type is REAL
}

//
// create a node for a number
//
AST_NODE *number(double value, DATA_TYPE dtype) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.retVal.val = value;
    p->data.number.retVal.type = dtype;


    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *opList) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    p->data.function.opList = opList;

    AST_NODE *scanner = p->data.function.opList;

    while (scanner != NULL) {
        scanner->parent = p;
        scanner = scanner->next;
    } //This should set all nodes in opList to have their parent -> p

    return p;
}

AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbolTable, AST_NODE *s_expr) {
    //if s_expr is NULL, return NULL (there is no parent node)
    if (s_expr == NULL)
        return NULL;

    s_expr->symbolTable = symbolTable;

    while (symbolTable != NULL){
        //go through symbolTable, assigning each symbol value parent to the input s_expr
        symbolTable->val->parent = s_expr;
        symbolTable = symbolTable->next;
    }

    return s_expr;
}

AST_NODE *symbol(char *name) {
    AST_NODE *p;
    size_t nodeSize;

    //allocate memory for an AST_NODE storing a SYMBOL_AST_NODE
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL) //malloc(nodeSize)
        yyerror("out of memory");

    p->type = SYMBOL_TYPE;

    //set the AST_NODE*'s name (in the symbol_ast_NODE portion of the union) to the input string
    nodeSize = sizeof(name)+1;
    if ((p->data.symbol.name = calloc(1,nodeSize)) == NULL)
        yyerror("out of memory"); //technically, we print the error but don't return an error, so the program may fault later if t tries to access the name...?
    else
        strcpy(p->data.symbol.name, name);

    return p;
}

SYMBOL_TABLE_NODE *createSymbol(char *name, AST_NODE *val, DATA_TYPE dtype) {
    if (val == NULL) {
        yyerror("Attempted to create a symbol with AST_NODE of NULL.");
        return NULL;
    }

    SYMBOL_TABLE_NODE *p;
    size_t nodeSize;

    //allocate memory for a SYMBOL_TABLE_NODE
    nodeSize = sizeof(SYMBOL_TABLE_NODE);
    if ((p = calloc(1, nodeSize)) == NULL) //malloc(nodeSize)
        yyerror("out of memory");

    p->ident = name;

    p->val = number(eval(val).val, dtype);
    if ((dtype == INT_TYPE)&&(eval(val).type == REAL_TYPE)) {
        //if type was REAL & new type is INT, trunc the decimals on the stored value
        p->val->data.number.retVal.val = trunc(p->val->data.number.retVal.val);
        fprintf(stderr, "WARNING: precision loss in the assignment for variable %s\n", name);
    }

    //TODO: Now that I've eval'd the tree with root *val, I should free this tree, right?

    return p;
}

SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol) {
    //if newSymbol is NULL, return the symbolTable
    if (newSymbol == NULL)
        return symbolTable;

    SYMBOL_TABLE_NODE *p = findSymbol(symbolTable, newSymbol);

    if (p==NULL) {
        //if result if NULL (ie. if symbol isn't in the list)
        newSymbol->next = symbolTable;
        return newSymbol;
    } else {
        yyerror("Symbol already present: newSymbol value has overwritten old symbol val");
        free(p->val);
        p->val = newSymbol->val;
    }
    return p;
}

SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol) {
    //if symbol is NULL, return NULL
    if (symbol == NULL)
        return NULL;

    SYMBOL_TABLE_NODE *p = symbolTable;
    //go through symbolTable (it's a linked list)
    while (p != NULL) {
        //if a node in symbolTable has the same ident value as symbol, return that node
        if (!strcmp(p->ident,symbol->ident))
            return p;
        p = p->next;
    }

    return NULL;
}

SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node) {
    //node is our SYMBOL ast_node, PARENT is the function that is trying to use the SYMBOL value (if nested functions, then we might have a PARENT of the PARENT of the SYMBOL, where the most global parent has the symbol in it's symbol table)
    AST_NODE *parent = node;
    SYMBOL_TABLE_NODE *symbol;

    while (parent != NULL) {
        symbol = parent->symbolTable;
        //set the symbol table that w are checking to the symbol table of the node's parent
        while (symbol != NULL) {
            //symbol == NULL when there is no symbol table
            if (!strcmp(symbol->ident, name)) //strcmp returns 0 (false) if both strings match - we want it to return true, so !(0)
                return symbol; //if names match, return the SYMBOL_TABLE_NODE that has the matched name and value pointer
            symbol = symbol->next; //if did not match, check the next item in the linked list;
        }
        //if no match in that symbol table, check the parent's symbol table of this parent
        parent = parent->parent;
    }

    return NULL;
}

//
// free a node
//
void freeNode(AST_NODE *p) {
    if (!p)
        return;

    if (p->next != NULL)
        freeNode(p->next); ///This removes all nodes in opLists

    switch (p->type)
    {
        case NUM_TYPE:
            //nothing to free within num union
            break;
        case FUNC_TYPE:
            free(p->data.function.name);
            freeNode(p->data.function.opList);
            break;
        case SYMBOL_TYPE:
            free(p->data.symbol.name);
            break;
    }

    free(p);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
RETURN_VALUE eval(AST_NODE *p) {

    RETURN_VALUE retVal;
    retVal.type = NAN_TYPE;
    retVal.val = NAN;
    //double retVal = NAN;

    if (!p)
        return retVal;

    RETURN_VALUE op2Val;
    op2Val.val = NAN;
    op2Val.type = NAN_TYPE;

    //+5points extra credit for implementing: square root, take second input as input, make a tailor series approximation up to that degree

    switch (p->type) {
        case SYMBOL_TYPE:
        {
            SYMBOL_TABLE_NODE *symbol;
            symbol = resolveSymbol(p->data.symbol.name,p);
            if (symbol != NULL)
                return eval(symbol->val); //if symbol is not def, throw error
            yyerror("Attempted to get the value of a symbol that has not yet been declared!");
        }
        case NUM_TYPE:
            return p->data.number.retVal;
        case FUNC_TYPE:
            if (p->data.function.opList != NULL)
            {
                retVal = eval(p->data.function.opList);

                //resolve func is not that resource intensive, so I'm calling it multiple times to save typing and keep readability
                switch (resolveFunc(p->data.function.name)) {
                    case NEG_OPER:
                    case ABS_OPER:
                    case EXP_OPER:
                    case SQRT_OPER:
                    case LOG_OPER:
                    case EXP2_OPER:
                    case CBRT_OPER:
                        //all these REQUIRE ONLY 1 parameter!
                        if (p->data.function.opList->next != NULL)
                            yyerror("More parameters passed than required, ignoring extra parameters!");
                        break;
                    case SUB_OPER:
                    case DIV_OPER:
                    case REMAINDER_OPER:
                    case POW_OPER:
                    case MAX_OPER:
                    case MIN_OPER:
                    case HYPOT_OPER:
                        //all these REQUIRE EXACTLY 2 parameters!
                        if (p->data.function.opList->next != NULL)
                            if (p->data.function.opList->next->next != NULL)
                                yyerror("More parameters passed than required, ignoring extra parameters!");
                    case ADD_OPER:
                    case MULT_OPER:
                    case PRINT_OPER:
                        //all these require 2 OR MORE parameters
                        if (p->data.function.opList->next != NULL)
                            op2Val = eval(p->data.function.opList->next);
                        else
                            yyerror("1 parameter provided, not enough to complete function!");
                        break;
                }
                /*
                 * No need to do anything other than print errors, since if we don't eval the next parameter
                 * then the default value will be NAN, and any function that accepts NAN as a parameter will
                 * automatically return NAN.
                 */

                switch (resolveFunc(p->data.function.name)) {
                    case NEG_OPER:
                        retVal.val *= -1;
                        break;
                    case ABS_OPER:
                        retVal.val = fabs(retVal.val);
                        break;
                    case EXP_OPER:
                        retVal.val = exp(retVal.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case SQRT_OPER:
                        retVal.val = sqrt(retVal.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case ADD_OPER:
                    {
                        retVal.val += op2Val.val;
                        AST_NODE *scanner = p->data.function.opList->next->next;
                        while (scanner != NULL)
                        {
                            retVal.val += eval(scanner).val;
                            if (eval(scanner).type == REAL_TYPE)
                                retVal.type = REAL_TYPE;
                            else if (eval(scanner).type == NAN_TYPE) {
                                retVal.val = NAN;
                                break;
                            }
                            scanner = scanner->next;
                        }
                        break;
                    }
                    case SUB_OPER:
                        retVal.val -= op2Val.val;
                        break;
                    case MULT_OPER:
                    {
                        retVal.val *= op2Val.val;
                        AST_NODE *scanner = p->data.function.opList->next->next;
                        while (scanner != NULL) {
                            retVal.val *= eval(scanner).val;
                            if (eval(scanner).type == REAL_TYPE)
                                retVal.type = REAL_TYPE;
                            else if (eval(scanner).type == NAN_TYPE) {
                                retVal.val = NAN;
                                break;
                            }
                            scanner = scanner->next;
                        }
                        break;
                    }
                    case DIV_OPER:
                        if (op2Val.val == 0) {
                            //retVal.type = NAN_TYPE; //done at end of eval func anyways
                            retVal.val = NAN;
                            break; //returns NAN
                        }
                        retVal.val = retVal.val / op2Val.val;
                        break;
                    case REMAINDER_OPER:
                        retVal.val = remainder(retVal.val, op2Val.val);
                        break;
                    case LOG_OPER:
                        ///DESIGN CHOICE: Only accept one varriable for log, and do the std log func
                        retVal.val = log(retVal.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case POW_OPER:
                        retVal.val = pow(retVal.val, op2Val.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case MAX_OPER:
                        retVal.val = fmax(retVal.val, op2Val.val);
                        break;
                    case MIN_OPER:
                        retVal.val = fmin(retVal.val, op2Val.val);
                        break;
                    case EXP2_OPER:
                        retVal.val = exp2(retVal.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case CBRT_OPER:
                        retVal.val = cbrt(retVal.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case HYPOT_OPER:
                        retVal.val = hypot(retVal.val, op2Val.val);
                        retVal.type = REAL_TYPE; ///DESIGN CHOICE: Always return a REAL value
                        break;
                    case PRINT_OPER:
                    {
                        if (retVal.type == REAL_TYPE)
                            printf("=> %.2lf", retVal.val); //if type is REAL, then print number with 2 decimal precision
                        else
                            printf("=> %.0lf", retVal.val); //else, print number without decimal (if NAN, it will print nan just fine)
                        AST_NODE *scanner = p->data.function.opList->next;
                        while (scanner != NULL)
                        {
                            if (scanner->data.number.retVal.type == REAL_TYPE)
                                printf(" %.2lf", eval(scanner).val);
                            else
                                printf(" %.0lf", eval(scanner).val);
                            scanner = scanner->next;
                        }
                        printf("\n");
                        break;
                    }
                    default: //CUSTOM_FUNC - not used?
                        break;
                } //end switch (function.name)
            } //end if (opList != NULL)
            else
                yyerror("0 parameters provided, not enough to complete function!"); //the function will then return NAN
    } //end switch (p->type)

    if (retVal.val == NAN) //this may happen as a result of a built-in function, so just double checking that the correct TYPE is assigned
        retVal.type = NAN_TYPE;

    if (retVal.type == INT_TYPE) //AKA, if retVal is not a REAL or NAN,
        if (op2Val.type == REAL_TYPE) //and if any other parameter passed IS a REAL
            retVal.type = REAL_TYPE; //then make the retVal a REAL.
            //else, return the type retVal already had

    return retVal;
}  

