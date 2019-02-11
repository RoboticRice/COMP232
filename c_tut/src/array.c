#include <stdio.h>

#define MAX_NUM_OF_CELLS 10

int main(void) {
    int numCells;

    puts("How many doubles?");
    scanf("%d", &numCells);

    if (numCells > MAX_NUM_OF_CELLS) {
        printf("The entered value of %d is to large. Value is now: ", numCells);
        numCells = MAX_NUM_OF_CELLS;
        printf("%d\n", numCells);
    }

    printf("Provide %d doubles:", numCells);

    double number[numCells];
    double sum = 0;
    double inputVal;

    for (int index = 0; index < numCells; index++) {
        scanf("%lf", &inputVal);
        number[index] = inputVal;
    }

    printf("Data: ");
    for (int index = 0; index < numCells; index = index + 1) {
        printf("%lf ", number[index]);
        sum += number[index];  /* sum array elements */
    }

    printf("\nAverage: %lf", sum/numCells);

    return 0;
}
