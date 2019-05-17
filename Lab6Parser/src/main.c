/**
* Name: RoboticRice
* Lab: Lab 6 Parser
* Date: 03/06/2019
**/

#include "eval.h"

int main(int argc, char** argv)
{
    freopen(argv[1], "r", stdin);

    NODE *fullProgram = program();
    printf("Done parsing...\n");
    printProgram(fullProgram);

    exit(0);
}