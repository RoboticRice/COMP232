#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr;
    /* allocate space to hold an int */
    ptr = (int *) malloc(sizeof(int)); //allocate memory that is the sizeof() the datatype int, and return an int pointer that points to that address

    /* do stuff with the space */
    *ptr = 4;

    free(ptr);
    /* free up the allocated space */


    //* the value of varriable
    //& the address of varriable
    /****************************************
     *        * ptr          * int          *
     ****************************************
     *value   * AddressOfI   * ValueofInt   *
     ****************************************
     *address * AddressOfPtr * AddressOfInt *
     ****************************************
     */
    /***********************
    *        * ptr  * int  *
    ************************
    *value   * ptr  * *ptr *
    ************************
    *address * &ptr * ptr  *
    ************************
    */
    return 0;
}
