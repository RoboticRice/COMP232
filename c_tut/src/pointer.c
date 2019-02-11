#include <stdio.h>

int main(void) {

    int j = 1;  // what is j now?
    //J value = 1
    //J addrs = Jadrs

    int *ptr = &j; /* initialize ptr before using it */
    //ptr value = Jadrs
    //ptr addrs = Padrs
    //J value = 1
    //J addrs = Jadrs

    *ptr = 4;   // what is j now?
    //J value = 4

    j = *ptr;   // what is j now?
    //J value = 4

    return 0;
}
