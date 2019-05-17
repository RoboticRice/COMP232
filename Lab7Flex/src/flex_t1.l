/* NOTE: % must be in the first column (no indentation) */

%option noyywrap
%option nounput
%option noinput

ws              [ \t\n]
digit           [0-9]
letter          [a-zA-Z]
number          {digit}+(\.{digit}+)?
id              {letter}+({letter}|{digit}|_)*

%{
   #include "flex_t1.h"
%}

%%

"if"        {return IF_TOKEN;}
"then"      {return THEN_TOKEN;}
"do"        {return DO_TOKEN;}
"while"     {return WHILE_TOKEN;}
"print"     {return PRINT_TOKEN;}
{number}    {return NUMBER_TOKEN;}
{id}        {return ID_TOKEN;}
"("         {return LPARAN_TOKEN;}
")"         {return RPARAN_TOKEN;}
"="         {return ASSIGN_TOKEN;}
"+"         {return PLUS_TOKEN;}
"-"         {return MINUS_TOKEN;}
"/"         {return DIV_TOKEN;}
"*"         {return MULT_TOKEN;}
"%"         {return MOD_TOKEN;}
";"         {return SEMI_TOKEN;}
{ws}        {return WS_TOKEN;}

%%

void yyerror(char *s) {/* dummy */}
