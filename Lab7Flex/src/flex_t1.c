/**
* Name: RoboticRice
* Lab: Lab 7 Flex
* Date: 03/13/209
**/

#include "flex_t1.h"

extern char *yytext;

int main(int argc, char **argv) {

    freopen(argv[1], "r", stdin);

    TOKEN tok;

    char *token[] = {
            "if",
            "then",
            "do",
            "while",
            "print",
            "number",
            "id",
            "lparan",
            "rparan",
            "assignment",
            "plus",
            "minus",
            "divide",
            "multiply",
            "modulus",
            "semicolon"//,
            //"whiteSpace" //not required, as we don't call this spot
    };

    while ((tok = yylex()) != 0) {
        if (tok <= PRINT_TOKEN)
            printf("{<keyword> \"%s\"}\n", token[tok - IF_TOKEN]);
        else if (tok == WS_TOKEN);
            //do nothing
        else
            printf("{<%s> \"%s\"}\n", token[tok - IF_TOKEN], yytext);
    }
}