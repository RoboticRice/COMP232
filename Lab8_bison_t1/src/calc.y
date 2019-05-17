/*

* Name: RoboticRice
* Lab: Lab 8 Bison - Part 1
* Date: 04/2/19

A grammar for the s-expressions calculator:

program ::= s-expr <end-of-line>
s-expr ::= number | f-expr
f-expr ::= ( func s-expr ) | ( func s-expr s-expr )
number ::= [ + | - ] digit+ [ . digit+ ]
digit ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

*/

%{
   #include "calc.h"
%}

%union // yylval
{
    double dval;
    char *sval;
}

%token <sval> FUNC
%token <dval> NUMBER
%token LPAREN RPAREN EOL QUIT

%type <dval> s_expr f_expr

%%

program:
   s_expr EOL {
      fprintf(stderr, "yacc: program ::= s_expr\n");
      printf("%lf\n", $1);
   };

s_expr:
   NUMBER {
      fprintf(stderr, "yacc: s_expr ::= NUMBER\n");
      $$ = $1;
   }
   | f_expr {
      $$ = $1;
   };


f_expr:
   LPAREN FUNC s_expr RPAREN {
      fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr RPAREN\n");
      $$ = calc($2, $3, NAN); //NAN is better than 0, as 0 can be an intentional input, but it does not differentiate between computational error and lack of input
      fprintf(stderr, "src returns %lf\n", $$);
   }
   | LPAREN FUNC s_expr s_expr RPAREN {
      fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr expr RPAREN\n");
      $$ = calc($2, $3, $4);
      fprintf(stderr, "src returns %lf\n", $$);
   }
   | QUIT {
      fprintf(stderr, "yacc: s_expr ::= QUIT\n");
      exit(0);
   }
%%

