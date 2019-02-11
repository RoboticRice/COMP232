#include <stdio.h>

#include "person.h"

#define ARRAY_SIZE 3

int main(void) {
    PERSON employees[ARRAY_SIZE];

    for (int i=0; i<ARRAY_SIZE; i++){
        addEmployee(&employees[i]);
    }
    puts("--------------");
    displayEmployee(&employees[0]);
    puts("--------------");
    displayAllEmployees(employees, ARRAY_SIZE);

    return 0;
}
