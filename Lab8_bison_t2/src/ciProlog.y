/*

 logexpr ::= 
   proposition
 | assert ( proposition )
 | retract ( proposition )
 | ( logexpr )
 | NOT logexpr
 | logexpr AND logexpr
 | logexpr OR logexpr

 letter ::= [a-zA-Z]
 proposition ::= '{letter}({letter}|\ )*'

 */

%{
#include "ciProlog.h"
%}

%union
{
   bool bval;
   char *sval;
}

%token <sval> PROPOSITION
%token ASSERT RETRACT NOT AND OR LPAREN RPAREN EOL HALT

%type <bval> logexpr

%%

program:
	logexpr EOL {
        	fprintf(stderr, "yacc: program ::= logexpr EOL\n");
        	printf("=> %s\n", bool2str($1));
	}
;

logexpr:
	PROPOSITION {
		fprintf(stderr, "yacc: logexpr ::= PROPOSITION\n");
		$$ = eval($1);
	}
	| ASSERT LPAREN PROPOSITION RPAREN {
		$$ = assert($3);
	}
	| RETRACT LPAREN PROPOSITION RPAREN {
		$$ = retract($3);
	}
        | LPAREN logexpr RPAREN {
        	$$ = $2;
        }
        | NOT logexpr {
        	$$ = not($2);
        }
	| logexpr AND logexpr {
		$$ = and($1, $3);
	}
        | logexpr OR logexpr {
        	$$ = or($1, $3);
        }
	| HALT {
  		fprintf(stderr, "yacc: logexpr ::= HALT\n");
   		exit(0);
	}
;

%%

