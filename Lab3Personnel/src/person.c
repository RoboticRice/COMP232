/**
 * Name: RoboticRice
 * Lab: 3 Personnel
 * Date: 02/18/2019
**/

#include "person.h"

LIST *head = NULL, *tail = NULL;

void inputPersonalData(PERSON *person)
{
    puts("New Record:");
    puts("Name:");
    scanf("%41s", person->name); //the 41 sets the input buffer size
    puts("Age:");
    scanf("%i", &person->age);
    puts("Height:");
    scanf("%f", &person->height);
    puts("Birthday in MM/DD/YYYY:");
    scanf("%i/%i/%i", &person->bday.month, &person->bday.day, &person->bday.year);
    puts("");//aka, newline
    //addPersonalDataToDatabase(person); //this is done in the main
}

void addPersonalDataToDatabase(PERSON *person)
{
    add(&head, &tail, person);
}

void displayDatabase()
{
    if (head == NULL){
        puts("No people in records!");
    } else {
        LIST *currNode = head;
        LIST *nextNode = NULL;
        do {
            nextNode = currNode->next;

            if (currNode->data != NULL)
                displayPerson(currNode->data);

            currNode = nextNode;

        } while (currNode != NULL);
    }
}

void displayPerson(PERSON *person)
{
    printf("Name: %s\n", person->name);
    printf("Age: %i\n", person->age);
    printf("Height: %f\n", person->height);
    printf("Birthday: %i/%i/%i\n\n", person->bday.month, person->bday.day, person->bday.year);
}

PERSON *findPersonInDatabase(char *name)
{
    if (head == NULL){
        puts("No people in records!");
    } else {
        LIST *currNode = head;
        LIST *nextNode = NULL;
        PERSON* person = NULL;
        do {
            nextNode = currNode->next;

            if (currNode->data != NULL) {
                person = (PERSON*)(currNode->data);
                if (strcmp(person->name, name) == 0) {
                    return (PERSON*) currNode->data; //PLTL said this should be explicit
                }
            }

            currNode = nextNode;

        } while (currNode != NULL);
    }
    return NULL; // if not found
}

void removePersonFromDatabase(char *name)
{
    delete(&head, &tail, findPersonInDatabase(name));
}

void clearDatabase()
{
    clearRecursively(&head, &tail);
    head = tail = NULL;
}
