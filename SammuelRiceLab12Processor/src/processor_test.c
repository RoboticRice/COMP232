#include "processor.h"

int main(void)
{
    char inputBuffer[BUFFER_SIZE];

    while(true)
    {
        // get a line of input from the user
        scanf(" %[^\n]", inputBuffer);
        if (strncmp(inputBuffer, SENTINEL, SENTINEL_LEN) == 0)
        {
            // stop when the SENTINEL is read in, but still process the remaining messages first
            messageDispatcher();
            printStatistics();
            break;
        }
        // add the message to the cache
        addMessageToCache(inputBuffer);
    }
}
