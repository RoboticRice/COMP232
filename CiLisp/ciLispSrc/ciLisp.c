

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
                //TODO TASK 6:
                "rand", //generate a random double, by any means
                "read", //scanf from user to get value
                "equal", //return T/F (0 or 1)
                "smaller", //return T/F (0 or 1)
                "larger", //return T/F (0 or 1)
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
AST_NODE *number(double value, DATA_TYPE dtype)
{
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed size and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL) //malloc(nodeSize)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.retVal.val = value;
    p->data.number.retVal.type = dtype;

    //p->parent=NULL; //no longer needed due to calloc

    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *opList)
{
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL) //malloc(nodeSize)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    p->data.function.opList = opList;

    if (opList != NULL) { //==NULL only when nothing has been provided
        p->data.function.opList->parent = p;
        p->data.function.opList->symbolTable = p->symbolTable;
    }
    //TODO: should the parent of each element in the linked list "opList" be * to the function's AST_NODE, or just the first element?

    //p->parent=NULL; //No longer needed due to calloc

    return p;
}

AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbolTable, AST_NODE *s_expr)
{
    //if s_expr is NULL, return NULL (there is no parent node)
    if (s_expr == NULL)
        return NULL;

    //set s_expr's symbolTable to the one input
    s_expr->symbolTable = symbolTable; //no need to malloc b/c we are changing the address of the pointer to an already existing object

    while (symbolTable != NULL){
        //go through symbolTable, assigning each symbol value parent to the input s_expr
        symbolTable->val->parent = s_expr;
        symbolTable = symbolTable->next;
    }

    return s_expr;
}

AST_NODE *symbol(char *name) //for making an AST node, when a symbol is used to ref it's value
{
    AST_NODE *p;
    size_t nodeSize;

    //allocate memory for an AST_NODE storing a SYMBOL_AST_NODE
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL) //malloc(nodeSize)
        yyerror("out of memory");

    //set the AST_NODE*'s type (symbol)
    p->type = SYMBOL_TYPE;

    //set the AST_NODE*'s symbolTable and parent to NULL //calloc takes care of this for us
    //p->symbolTable = NULL;
    //p->parent = NULL;

    //set the AST_NODE*'s name (in the symbol_ast_NODE portion of the union) to the input string
    nodeSize = sizeof(name)+1;
    if ((p->data.symbol.name = calloc(1,nodeSize)) == NULL)
        yyerror("out of memory"); //technically, we print the error but don't return an error, so the program may fault later if t tries to access the name...?
    else
        strcpy(p->data.symbol.name, name);

    return p;
}

SYMBOL_TABLE_NODE *createSymbol(char *name, AST_NODE *val, DATA_TYPE dtype)
{
    //if val is NULL, return NULL (maybe print a warning? symbol with no value?) //should never happen
    if (val == NULL)
        return NULL;

    SYMBOL_TABLE_NODE *p;
    size_t nodeSize;

    //allocate memory for a SYMBOL_TABLE_NODE
    nodeSize = sizeof(SYMBOL_TABLE_NODE);
    if ((p = calloc(1, nodeSize)) == NULL) //malloc(nodeSize)
        yyerror("out of memory");



    //set the SYMBOL_TABLE_NODE*'s ident to input name
//    nodeSize = sizeof(name)+1;
//    if ((p->ident = malloc(nodeSize)) == NULL)
//        yyerror("out of memory");
//    else
//        strcpy(p->ident, name);
    p->ident = name;

    //set the SYMBOL_TABLE_NODE*'s next pointer to NULL
    p->next = NULL;

    /*TODO This block should move to setSymbolTable*/
    //set the SYMBOL_TABLE_NODE*'s val to the input val
    //TODO eval stuff, free stuff, then set stuff to number that is result - this is when my code broke
//    RETURN_VALUE result = eval(val);
//    freeTree(val);
//    nodeSize = sizeof(AST_NODE);
//    if ((val = calloc(1, nodeSize)) == NULL)
//        yyerror("out of memory");
//    val->type = NUM_TYPE;
//    val->data.number.retVal = result;
//
//    if ((dtype == INT_TYPE)&&(val->data.number.retVal.type == REAL_TYPE)) {
//        //if type was REAL & new type is INT, trunc the decimals on the stored value
//        val->data.number.retVal.val = trunc(val->data.number.retVal.val);
//        fprintf(stderr, "WARNING: precision loss in the assignment for variable %s\n", name);
//    }
//    val->data.number.retVal.type = dtype;
    /*TODO END BLOCK*/

    p->val = val;

    return p;
}

SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol)
{
    //if newSymbol is NULL, return the symbolTable
    if (newSymbol == NULL)
        return symbolTable;

    //call findSymbol with symbolTable and newSymbol
    SYMBOL_TABLE_NODE *p = findSymbol(symbolTable, newSymbol);
    //if result if NULL (ie. if symbol isn't in the list
    if (p==NULL) {
        //set newSymbol next pointer to symbolTable
        //return newSymbol (it's now the head)
        newSymbol->next = symbolTable;
        return newSymbol;
    } else {
        //symbol is already there, so change it's value
        //print something MAD!
        yyerror("symbol already present: newSymbol value has overwritten old symbol val");
        //free something, overwriting old linked list, so free old
        free(p->val);
        size_t nodeSize = sizeof(SYMBOL_TABLE_NODE);
        if ((p->val = malloc(nodeSize)) == NULL)
            yyerror("out of memory");
        p->val = newSymbol->val;
        return p;
    }
}

SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol) //only used in addSymbolToList
{
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

SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node) //only used in eval method
{
    //set "parent" to node
    AST_NODE *parent = node;
    SYMBOL_TABLE_NODE *symbol;
    //while parent is not NULL:
    while (parent != NULL){
        //set "symbol" to parent's symbolTable
        symbol = parent->symbolTable;
        //while symbol is not NULL:
        while (symbol != NULL) {
            //if symbol ident is the same as input name, return symbol
            if (!strcmp(symbol->ident, name)) //TODO this only EXC_BAD_ACCESS with nested LET calls, can't figure it out
                return symbol;
            symbol = symbol->next;
        }
        //set parent to parent's -> parent
        parent = parent->parent;
    }
    return NULL;
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
        freeNode(p->data.function.opList); //TODO FREE THE ENTIRE LIST! NOT JUST THE FIRST ITEM!
        //freeNode(p->data.function.op2);
    }

    free(p);
}

//
// free a node
//
void freeTree(AST_NODE *p)
{
    if (!p)
        return;

    AST_NODE *cur = p;
    AST_NODE *next;

    do{
        next = cur->parent;
        freeNode(cur);
        cur = next;
    }while(cur);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
RETURN_VALUE eval(AST_NODE *p)
{
    RETURN_VALUE retVal;
    retVal.val = NAN;
    retVal.type = NAN_TYPE;
    if (!p) {
        return retVal;
    }

    RETURN_VALUE op2Val;
    op2Val.val = NAN;
    op2Val.type = NAN_TYPE;

    //+5points extra credit for implementing: square root, take second input as input, make a tailor series approximation up to that degree

    switch (p->type){
        case SYMBOL_TYPE:
        {
            SYMBOL_TABLE_NODE *symbol;
            symbol = resolveSymbol(p->data.symbol.name,p);
            if (symbol != NULL)
                return eval(symbol->val); //if symbol is not def, throw error
            yyerror("attempted to get the value of a symbol that has not yet been declared!");
        }
        case NUM_TYPE:
            return p->data.number.retVal;
        case FUNC_TYPE:
            //TODO move the check for opList != NULL here because every FUNC requires at least one op
            switch (resolveFunc(p->data.function.name)){
                case NEG_OPER:
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next==NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                            retVal = eval(p->data.function.opList); //first item in the list
                            retVal.val = -1 * retVal.val;
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal; //in the event the if condition does not run, it returns NAN
                case ABS_OPER:
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next==NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                        retVal = eval(p->data.function.opList);
                        retVal.val = fabs(retVal.val);
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case EXP_OPER:
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next==NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                            retVal = eval(p->data.function.opList);
                            retVal.val = exp(retVal.val);
                            retVal.type = REAL_TYPE;
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case SQRT_OPER:
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next == NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                            retVal = eval(p->data.function.opList);
                            retVal.val = sqrt(retVal.val);
                            retVal.type = REAL_TYPE;
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case ADD_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next != NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        retVal = eval(p->data.function.opList);
                        op2Val = eval(p->data.function.opList->next); //TODO make this dynamic size
                        retVal.val += op2Val.val;
                        if (op2Val.type == REAL_TYPE) //don't need to check retVal, b/c if retval is REAL, then we don't need to SETit to REAL lol
                            retVal.type = REAL_TYPE;
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case SUB_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next != NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        retVal = eval(p->data.function.opList);
                        op2Val = eval(p->data.function.opList->next);  //TODO make this dynamic size
                        retVal.val -= op2Val.val;
                        if (op2Val.type == REAL_TYPE)
                            retVal.type = REAL_TYPE;
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case MULT_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        retVal = eval(p->data.function.opList);
                        op2Val = eval(p->data.function.opList->next);  //TODO make this dynamic size
                        retVal.val *= op2Val.val;
                        if (op2Val.type == REAL_TYPE)
                            retVal.type = REAL_TYPE;
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case DIV_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        op2Val = eval(p->data.function.opList->next);  //TODO make this dynamic size
                        if (op2Val.val!=0){
                            retVal = eval(p->data.function.opList);
                            retVal.val = retVal.val / op2Val.val;
                            if ((op2Val.type == REAL_TYPE) | (retVal.val - (int) retVal.val !=0) )
                                retVal.type = REAL_TYPE;
                        }
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;//retVal default is NAN
                case REMAINDER_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        retVal = eval(p->data.function.opList);
                        op2Val = eval(p->data.function.opList->next);  //TODO make this dynamic size
                        retVal.val = remainder(retVal.val, op2Val.val);
                        //if (retVal.type == REAL_TYPE | op2Val.type == REAL_TYPE) //design choice, I chose to always return real
                        retVal.type = REAL_TYPE;
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case LOG_OPER: //design choice, only handle the default log
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next==NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                            retVal = eval(p->data.function.opList);
                            retVal.val = log(retVal.val);
                            retVal.type = REAL_TYPE;
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case POW_OPER: //design choice, require exactly 2
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        if (p->data.function.opList->next->next == NULL) {
                            //AKA, the 3rd item in the list is NULL (exactly 2 items)
                            retVal = eval(p->data.function.opList);
                            op2Val = eval(p->data.function.opList->next);
                            retVal.val = pow(retVal.val, op2Val.val);
                            if (op2Val.type == REAL_TYPE)
                                retVal.type = REAL_TYPE;
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case MAX_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        retVal = eval(p->data.function.opList);
                        op2Val = eval(p->data.function.opList->next);  //TODO make this dynamic size
                        retVal.val = fmax(retVal.val, op2Val.val);
                        if ((op2Val.type == REAL_TYPE) | (retVal.val - (int) retVal.val !=0) )
                            retVal.type = REAL_TYPE; //design choice: if either of input TYPEs are REAL, output must be REAL (even if the result is INT)
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case MIN_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                        //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                        retVal = eval(p->data.function.opList);
                        op2Val = eval(p->data.function.opList->next);  //TODO make this dynamic size
                        retVal.val = fmin(retVal.val, op2Val.val); //same as MAX
                        if ((op2Val.type == REAL_TYPE) | (retVal.val - (int) retVal.val !=0) )
                            retVal.type = REAL_TYPE;
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case EXP2_OPER:
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next==NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                            retVal = eval(p->data.function.opList);
                            retVal.val = exp2(retVal.val);
                            //retVal.type = REAL_TYPE; //if op1 is int, then result is int - if op2 is real, then result is real -- no need to assign
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case CBRT_OPER:
                    if (p->data.function.opList != NULL) {
                        if (p->data.function.opList->next==NULL) {
                            //AKA, the opList is not empty, and does not have a second element (only one element)
                            retVal = eval(p->data.function.opList);
                            retVal.val = cbrt(retVal.val);
                            retVal.type = REAL_TYPE; //design choice based on sqrt(), assume result always REAL
                        } else
                            yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case HYPOT_OPER:
                    if ((p->data.function.opList != NULL) && (p->data.function.opList->next!=NULL)) {
                            //AKA, the opList is not empty, and DOES have a second element (at least 2 elements)
                            if (p->data.function.opList->next->next == NULL) {
                                //AKA, the 3rd item in the list is NULL (exactly 2 items)
                                retVal = eval(p->data.function.opList);
                                op2Val = eval(p->data.function.opList->next);
                                retVal.val = hypot(retVal.val, op2Val.val);
                                if ((op2Val.type == REAL_TYPE) | (retVal.val - (int) retVal.val !=0) )
                                    retVal.type = REAL_TYPE;
                            } else
                                yyerror("Too many parameters provided!");
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                case PRINT_OPER: //should print each item separated by spaces, but return only the first item
                    if (p->data.function.opList != NULL) { //AKA, at least one item
                        retVal = eval(p->data.function.opList);
                        if (retVal.type == REAL_TYPE)
                            printf("=> %.2lf\n", retVal.val); //if type is REAL, then print number with 2 decimal precision
                        else
                            printf("=> %.0lf\n", retVal.val); //else, print number without decimal
                    } else
                        yyerror("Too few parameters provided!");
                    return retVal;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return retVal; //default NAN
}  

