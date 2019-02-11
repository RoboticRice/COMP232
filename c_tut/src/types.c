#include <stdio.h>5

int main(void) {
    int nStudents = 0; /* Initialization, required */
    int nFac = 0;
    double ratio;

    puts("How many students does CSUCI have ?:");
    scanf("%d", &nStudents);  /* Read input */
    printf("CSUCI has %d students.\n", nStudents);

    printf("How many faculty does CSUCI have?:");
    scanf("%d", &nFac);
    ratio = (double) nStudents / nFac;
    printf("CSUCI has a Student/Teacher ratio of %lf", ratio);
    return 0;
}
