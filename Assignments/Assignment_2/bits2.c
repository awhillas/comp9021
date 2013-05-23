/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the use of bitwise operators.                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    unsigned a = 0;
    
    a |= 1 << 6;
    a |= 1 << 3;
    a |= 1 << 8;

    int i = 0;
    while(a) {
        if(a & 1)
            printf("%d\n", i);
        a >>= 1;
        i++;
    }
    
    return EXIT_SUCCESS;
}

