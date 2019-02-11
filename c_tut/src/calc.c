#include <stdio.h>

int add(int, int);
int sub(int, int);
int mul(int, int);
int div(int, int);

int calc(int (*)(int, int), int, int);

int main(void) {
    int param1, param2;
    char operand;
    int (*f)(int, int);
    scanf("%i", &param1);
    operand = getchar();
    scanf("%i", &param2);
    switch (operand) {
        case '+' :
            f = add;
            break;
        case '-' :
            f = sub;
            break;
        case '*' :
            f = mul;
            break;
        case '/' :
            f = div;
            break;
        default :
            return 2;
    }
    printf("%i", calc(f, param1, param2));

    return 0;
}

int calc(int (*f)(int, int), int param1, int param2) {
    return (*f)(param1, param2);
}

int add(int param1, int param2) {
    return param1+param2;
}

int sub(int param1, int param2) {
    return param1-param2;
}

int mul(int param1, int param2) {
    return param1*param2;
}

int div(int param1, int param2) {
    return param1/param2;
}