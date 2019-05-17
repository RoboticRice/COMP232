/**
 * Name: Sammuel Rice
 * Lab: 1 2 Processor
 * Date: 02/06/2019
 * This header is only located in this file,
 * b/c this is the only file I changed. As
 * I was instructed to by Lab Prof.
**/

#include "processor.h"

MESSAGE messageCache[CACHE_SIZE];
int numMessagesRead = 0;

void addMessageToCache(char *inputLine)
{
    // Check input for type, then set messageCache.type & content
    MESSAGE *thisMessage = &messageCache[numMessagesRead];
    sscanf(inputLine, "%d %[^\n]", &thisMessage->type, inputLine); //converts string to int, assumes perfect user input
    switch (messageCache[numMessagesRead].type) {
        case MSG_TYPE_1 :
            thisMessage->content.string = malloc(sizeof(char) * (strlen(inputLine)+1));
            sscanf(inputLine, "%s", thisMessage->content.string);
            break;
        case MSG_TYPE_2 :
            //sscanf(inputLine, "%d %d %d %d %d", thisMessage->content.integers); //So I don't want to copy/paste this 5 times so...
            for (int i=0; i<NUM_OF_INTEGERS;i++){
                sscanf(inputLine, "%d %[^\n]", &thisMessage->content.integers[i], inputLine);
            } //While this does re-assign the inputLine var each time the for is called (and requires an extra int named i), I would argue that this if more useful for this application because it makes the code more dynamic (in the sense that the user can change the NUM_OF_INTEGERS and not have errors like the previous version) and is easier to read/write.
            break;
        case MSG_TYPE_3 :
            for (int i=0; i<NUM_OF_DOUBLES;i++){
                sscanf(inputLine, "%lf %[^\n]", &thisMessage->content.doubles[i], inputLine);
            }
            break;
        case MSG_TYPE_4 :
            for (int i=0; i<NUM_OF_STRINGS;i++){
                sscanf(inputLine, "%s %[^\n]", thisMessage->content.words[i], inputLine);
            }
            break;
    }
    numMessagesRead++;
}

void messageDispatcher(void)
{
    // calls process for every message
    for(int i=0;i<numMessagesRead;i++){
        processMessage(&messageCache[i]);
    }
}

void processMessage(MESSAGE *message)
{
    // read the MSG_TYPE and print based on type
    switch (message->type) {
        case MSG_TYPE_1 : //string unk size
            printf("TYPE 1: %s\n", message->content.string);
            free(message->content.string); //the string was allocated memory that won't be used anymore
            break;
        case MSG_TYPE_2 : //5 ints
            printf("TYPE 2: ");
            printf("%i", message->content.integers[0]); // two print statements so the "," is displayed correctly
            for (int i=1;i<NUM_OF_INTEGERS;i++){
                printf(",%i", message->content.integers[i]);
            }
            printf("\n");
            break;
        case MSG_TYPE_3 : //4 dbls
            printf("TYPE 3: ");
            printf("%lf", message->content.doubles[0]);
            for (int i=1;i<NUM_OF_DOUBLES;i++){
                printf("/%lf", message->content.doubles[i]);
            }
            printf("\n");
            break;
        case MSG_TYPE_4 : //5 words
            printf("TYPE 4: ");
            printf("%s", message->content.words[0]);
            for (int i=1;i<NUM_OF_STRINGS;i++){
                printf(" %s", message->content.words[i]);
            }
            printf("\n");
            break;
        default :
            //This should never happen? What about if there are less messages than cache_size?
            break;
    }
}

void printStatistics(void)
{
    printf("Number of message batches: %i\n", 1);
    puts("Messages processed:");
    printf("Total: %i\n", numMessagesRead);
    int count1, count2, count3, count4;
    count1=count2=count3=count4=0;
    for (int i = 0; i < numMessagesRead; i++) {
        switch (messageCache[i].type) {
            case MSG_TYPE_1 :
                count1++;
                break;
            case MSG_TYPE_2 :
                count2++;
                break;
            case MSG_TYPE_3 :
                count3++;
                break;
            case MSG_TYPE_4 :
                count4++;
                break;
        }
    }
    printf("Type 1: %i\n", count1);
    printf("Type 2: %i\n", count2);
    printf("Type 3: %i\n", count3);
    printf("Type 4: %i\n", count4);
}
