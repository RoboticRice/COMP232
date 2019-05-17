%option noyywrap
%option caseless
%option noinput
%option nounput

%{
    #include "ciProlog.h"
%}

l [a-zA-Z]
prop '{l}({l}|\ )*'

%%

"halt"      { return HALT; }
{prop} {
    yylval.sval = (char *) malloc(strlen(yytext) * sizeof(char));
    strcpy(yylval.sval, yytext);
    fprintf(stderr, "lex: PROPOSITION sval = %s\n", yylval.sval);
    return PROPOSITION;
}
"assert"    { return ASSERT; }
"retract"   { return RETRACT; }
"NOT"       { return NOT; }
"AND"       { return AND; }
"OR"        { return OR; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"\n"        {
                fprintf(stderr, "lex: EOL\n");
                return EOL;
            }

[ \t] {}    ; /* do nothing - skip whitespace */

.           yyerror("lex: invalid character");

%%

/*
 * DO NOT CHANGE THE FOLLOWING CODE CRITICAL FOR REPL!
 */
int main(void)
{
    freopen("/dev/null", "w", stderr); // except for this line that can be uncommented to throw away debug printouts

    initKnowledgeBase();

    char *s_expr_str = NULL;
    size_t s_expr_str_len = 0;
    YY_BUFFER_STATE buffer;
    while (true)
    {
        printf("\n?- ");
        getline(&s_expr_str, &s_expr_str_len, stdin);
        s_expr_str_len = strlen(s_expr_str);
        s_expr_str[s_expr_str_len++] = '\0';
        s_expr_str[s_expr_str_len++] = '\0';
        buffer = yy_scan_buffer(s_expr_str, s_expr_str_len);
        yyparse();
        yy_delete_buffer(buffer);
    }
}