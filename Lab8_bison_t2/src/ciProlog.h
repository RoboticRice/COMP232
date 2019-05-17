/**
* Name: RoboticRice
* Lab: Lab 8 Bison Part 2
* Date: 04/2/19
**/

#ifndef __ciProlog_h_
#define __ciProlog_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ciPrologParser.h"

int yyparse(void);
int yylex(void);
void yyerror(char *);

#define bool2str(b) ((b) == true ? "TRUE" : "FALSE")

typedef struct prop_type
{
   char *data;
   struct prop_type *next;
} PROP_TYPE;

void initKnowledgeBase(void);
bool assert(char*);
bool retract(char*);
bool eval(char*);
bool not(bool);
bool and(bool, bool);
bool or(bool, bool);

#endif
