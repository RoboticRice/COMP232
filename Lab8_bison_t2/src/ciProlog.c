/**
* Name: RiceRice
* Lab: Lab 8 Bison Part 2
* Date: 04/2/19
**/

#include "ciProlog.h"

// the knowledge base
// a linked list of propositions
// if a proposition is on the list, it is assumed to be true
// anything not on the list is false
// the first element is empty; it is used as an anchor for kb_head and kb_tail
// we always add at kb_tail
// we always search from kb_head->next;

PROP_TYPE *kb_head, *kb_tail;

void initKnowledgeBase(void)
{
    kb_head = kb_tail = (PROP_TYPE *) malloc(sizeof(PROP_TYPE)); // always empty head of the list
    kb_head->data = ""; // indicates the empty head; skip in searches
    kb_head->next = NULL;
}

void yyerror(char *s)
{
    fprintf(stderr, "yyerror: %s\n", s);
}

bool not(bool logexpr1)
{
    return !logexpr1; //TODO
}

bool and(bool logexpr1, bool logexpr2)
{
    return (logexpr1 && logexpr2);
}

bool or(bool logexpr1, bool logexpr2)
{
    return (logexpr1 | logexpr2);
}

// add the assertion to the database
// finding a proposition in the list makes it true
bool assert(char *proposition)
{
    PROP_TYPE *curNode = kb_head;
    PROP_TYPE *prvNode = kb_head;
    do {
        if (!strcmp(curNode->data, proposition)) {
            return false; //if found, then we can assert this!
        }
        else {
            prvNode = curNode;
            curNode = curNode->next;
        }
    } while (curNode != NULL); //happens when at the tail
    //not found, so add the node!
    PROP_TYPE *newNode = (PROP_TYPE *) malloc(sizeof(PROP_TYPE));
    newNode->data = malloc(sizeof(proposition));
    strcpy(newNode->data, proposition);
    newNode->next = NULL;
    prvNode->next = newNode;
    kb_tail = newNode;
    return true; //if you can not add to database, true if you can
}

// remove the assertion to the database
// after that the proposition is assumed to be false -- it cannot be found
bool retract(char *proposition)
{
    PROP_TYPE *curNode = kb_head;
    PROP_TYPE *prvNode = kb_head;
    do {
        if (!strcmp(curNode->data, proposition)) {
            prvNode->next = curNode->next;
            free(curNode->data);
            free(curNode);
            return true;
        }
        else {
            prvNode = curNode;
            curNode = curNode->next;
        }
    } while (curNode != NULL); //happens when at the tail
    return false; //if not in database, true if it is and it was removed
}

// find the proposition in the knowledge base
// if found, return true
// otherwise, return false
bool eval(char *proposition)
{
    PROP_TYPE* curNode = kb_head;
    do {
        if (!strcmp(curNode->data, proposition))
            return true;
        else
            curNode = curNode->next;
    } while (curNode != NULL); //happens when at the tail
    return false;
};
