//
// Created by Rice, Sammuel on 1/30/19.
//

#ifndef C_TUT_PERSON_H
#define C_TUT_PERSON_H

typedef struct {
    char name[41];
    int age;
    float height;
    struct {
        int month;
        int day;
        int year;
    } birth;
} PERSON;

void addEmployee(PERSON *employee);
void displayAllEmployees(PERSON employees[], int numberOfEmployees);
void displayEmployee(PERSON *employee);


#endif //C_TUT_PERSON_H
