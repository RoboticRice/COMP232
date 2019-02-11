//
// Created by Rice, Sammuel on 1/30/19.
//
#include <stdio.h>
#include "person.h"

void addEmployee(PERSON *employee){
    puts("New Employee:");
    puts("Name:");
    scanf("%s", employee->name);
    puts("Age:");
    scanf("%i", &employee->age);
    puts("Height:");
    scanf("%f", &employee->height);
    puts("Birth Month:");
    scanf("%i", &employee->birth.month);
    puts("Birth Day:");
    scanf("%i", &employee->birth.day);
    puts("Birth Year:");
    scanf("%i", &employee->birth.year);
}
void displayAllEmployees(PERSON employees[], int numberOfEmployees){
    for(int i = 0; i<numberOfEmployees; i++)
    {
        displayEmployee(&employees[i]);
    }
}
void displayEmployee(PERSON *employee){
    printf("Employee: %s\n", employee->name);
    printf("Age: %i\n", employee->age);
    printf("Height: %f\n", employee->height);
    printf("Birthday: %i/%i/%i\n", employee->birth.month, employee->birth.day, employee->birth.year);
}