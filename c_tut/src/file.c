#include <stdio.h>

#define MAX_SIZE 100

int main(void) {
	/* file handles */
	FILE *outputFile=NULL;
	FILE *inputFile=NULL;
	char fChar;

	/*open file for reading*/
	inputFile = fopen("data.txt", "r");
	if(inputFile == NULL)
		return(2);

	/* open files for writing*/
	outputFile = fopen("cwork.dat", "w");
	if(outputFile == NULL)
		return(1);    /* need to do explicit ERROR CHECKING */

    fChar = fgetc(inputFile);
	//while (!feof(inputFile)) //this reads the EOF char and says there's still a char there, only sets TRUE if no more char
	while (fChar != EOF)
	{
		fputc(fChar, outputFile);
        fChar = fgetc(inputFile);
	}

	/* write some data into the file */
    //fprintf(outputFile, "Hello there");
	
	/* don’t forget to close file handles */
	fclose(inputFile);
	fclose(outputFile);
	
    return 0;
}
