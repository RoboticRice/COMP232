#include <stdio.h>
#include <ctype.h>

/* like Java ‘final’ */
int main(void) {
    char level;

    /* if-then-else as in Java */

    puts("What lvl are we?");
    level = tolower(getchar());

    switch (level) {
        case 'f' :
            puts("Full!");
            break;
        case 'h' :
            puts("Half!");
            break;
        case 'e' :
            puts("Empty!");
            break;
        default:
            puts("Invalid!");
    }

    return 0;
}
