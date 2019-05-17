#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

#define DEF_NUM    1

int main(void)
{
    PERSON *person;

    int num;
    puts("Enter the initial number of records:");
    if (scanf("%d", &num) < 1)
        num = DEF_NUM;

    while (num-- > 0)
    {
        person = (PERSON *) malloc(sizeof(PERSON));
        inputPersonalData(person);
        addPersonalDataToDatabase(person);
    }

    displayDatabase();

    puts("\n--> Searching database for Maya");
    PERSON *maya = findPersonInDatabase("Maya");
    if (maya == NULL)
        puts("Maya not found");
    else
    {
        displayPerson(maya);
        puts("\n--> Removing Maya from database");
        removePersonFromDatabase("Maya");
    }
    displayDatabase();

// added to test finding and removing the last element
    puts("\n--> Searching database for Frank");
    PERSON *frank = findPersonInDatabase("Frank");
    if (frank == NULL)
        puts("Frank not found");
    else
    {
        displayPerson(frank);
        puts("\n--> Removing Frank from database");
        removePersonFromDatabase("Frank");
    }
    displayDatabase();

    puts("\n--> Removing Miro from database");
    removePersonFromDatabase("Miro");

    displayDatabase();


    puts("\n--> Adding new record to database");
    person = (PERSON *) malloc(sizeof(PERSON));
    inputPersonalData(person);
    addPersonalDataToDatabase(person);

    displayDatabase();

    puts("\n--> Clearing database");
    clearDatabase();

    displayDatabase();

    puts("\n--> Adding new record to database");
    person = (PERSON *) malloc(sizeof(PERSON));
    inputPersonalData(person);
    addPersonalDataToDatabase(person);

    displayDatabase();
}

