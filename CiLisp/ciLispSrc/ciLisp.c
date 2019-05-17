/*
 * ciLisp Project
 * RoboticRice
 * Task 2
 * In-Progress: 05/01/2019
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

//
// create a node for a number
//
AST_NODE *number(double value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value = value;

    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = calloc(1, nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    p->data.function.op1 = op1;
    p->data.function.op2 = op2;

    if (op1 != NULL) {
        p->data.function.op1->parent = p;
        //p->data.function.op1->symbolTable = p->symbolTable;
    }

    if (op2 != NULL) {
        p->data.function.op2->parent = p;
        //p->data.function.op2->symbolTable = p->symbolTable;
    }

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

SYMBOL_TABLE_NODE *createSymbol(char *name, AST_NODE *val) { //TODO later task// DATA_TYPE dtype) {
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

    //p->val = number(eval(val)); //TODO where/when do we eval this?
    p->val = val;

    //free(val); //TODO val might have sub items, do we need to free those too?

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

    switch (p->type)
    {
        case NUM_TYPE:
            //nothing to free within num union
            break;
        case FUNC_TYPE:
            free(p->data.function.name);
            freeNode(p->data.function.op1);
            freeNode(p->data.function.op2);
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
double eval(AST_NODE *p) {
    if (!p)
        return NAN;

    double retVal = NAN;

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

