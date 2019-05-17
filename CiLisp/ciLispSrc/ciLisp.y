%{
    #include "ciLisp.h"
%}

%union {
	double dval;
	char *sval;
	struct ast_node *astNode; //function values or just a number
	struct symbol_table_node *symbolNode;  //linked list, each element storing the name and value of varriable
};

%token <sval> FUNC SYMBOL TYPE
%token <dval> REAL_NUMBER INT_NUMBER
%token LPAREN RPAREN EOL QUIT LET

%type <astNode> s_expr f_expr s_expr_list
%type <symbolNode> let_elem let_section let_list

%%

program:
	s_expr EOL {
		fprintf(stderr, "yacc: program ::= s_expr EOL\n");
		if ($1) {
			printf("%lf", eval($1).val);
			freeNode($1);
		}
	};

s_expr:
	REAL_NUMBER {
		fprintf(stderr, "yacc: s_expr ::= REAL_NUMBER\n");
		$$ = number($1, REAL_TYPE);
	}
	| INT_NUMBER {
		fprintf(stderr, "yacc: s_expr ::= INT_NUMBER\n");
		$$ = number($1, INT_TYPE);
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
	LPAREN FUNC s_expr_list RPAREN {
		fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr RPAREN\n");
		$$ = function($2, $3);
	}

s_expr_list:
    s_expr s_expr_list {
        $1->next = $2;
        $$ = $1;
    }
    | s_expr {
        $$ = $1;
    }
    | {
        $$ = NULL;
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
	LPAREN TYPE SYMBOL s_expr RPAREN {
    		$$ = createSymbol($3, $4, resolveType($2));
    }
    | LPAREN SYMBOL s_expr RPAREN {
		$$ = createSymbol($2, $3, resolveType("NULL"));
	};
%%

