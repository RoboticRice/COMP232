#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 10
#define MAX_WLENG 15

int main(void)
{
    char *pArray[MAX_WORDS];
    char cString[MAX_WLENG];

    puts("Please type words:");

    int i; //use this counter outside of the for loop
    for (i = 0; i < MAX_WORDS; i++)
    {
        scanf("%s", &cString);
        if(!(strcmp(cString,"END\0")))
        {
            //i = MAX_WORDS+1;
            break;
        }
        else
        {
            pArray[i] = malloc(sizeof(char)*(strlen(cString)+1)); //allocate memory for the size of the string * the size of any char datatype
            strcpy(pArray[i],cString);
        }
    }

    printf("Number of words read: %i\n", i);

    for (int j = 0; j < i; j++)
    {
        printf("%s\n", pArray[j]);
        free(pArray[j]);
    }

    return 0;
}