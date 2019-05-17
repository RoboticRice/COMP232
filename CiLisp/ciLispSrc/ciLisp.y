%{
    #include "ciLisp.h"
%}

%union {
	double dval;
	char *sval;
	struct ast_node *astNode; //function values or just a number
	struct symbol_table_node *symbolNode;  //linked list, each element storing the name and value of varriable
};

%token <sval> FUNC SYMBOL
%token <dval> NUMBER
%token LPAREN RPAREN EOL QUIT LET

%type <astNode> s_expr f_expr
%type <symbolNode> let_elem let_section let_list

%%

program:
	s_expr EOL {
		fprintf(stderr, "yacc: program ::= s_expr EOL\n");
		if ($1) {
			printf("%lf", eval($1));
			freeNode($1);
		}
	};

s_expr:
	NUMBER {
		fprintf(stderr, "yacc: s_expr ::= NUMBER\n");
		$$ = number($1);
	}
	| SYMBOL {
		$$ = symbol($1);
	}
	| f_expr {
		$$ = $1;
	}
	| LPAREN let_section s_expr RPAREN {
		$$ = setSymbolTable($2, $3);
	}
	| QUIT {
		fprintf(stderr, "yacc: s_expr ::= QUIT\n");
		exit(EXIT_SUCCESS);
	}
	| error {
		fprintf(stderr, "yacc: s_expr ::= error\n");
		yyerror("unexpected token");
		$$ = NULL;
	};

f_expr:
	LPAREN FUNC s_expr RPAREN {
		fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr RPAREN\n");
		$$ = function($2, $3, 0);
	}
	| LPAREN FUNC s_expr s_expr RPAREN {
		fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr expr RPAREN\n");
		$$ = function($2, $3, $4);
	};

let_section:
	LPAREN let_list RPAREN {
		$$ = $2;
	}
	| {
		$$ = NULL;
	};

let_list:
	let_list let_elem {
		$$ = addSymbolToList($1, $2);
	}
	| LET let_elem {
		$$ = $2;
	};

let_elem:
	LPAREN SYMBOL s_expr RPAREN {
		$$ = createSymbol($2, $3);
	};
%%

