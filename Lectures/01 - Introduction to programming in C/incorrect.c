/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: This program is syntactically incorrect.                       *
 *              It fails to compile.                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int mian(void) {
    int n = 2;
    int m = 3;
    int sum = n + m;
    printf("The sum of %d and %d is: %d", n, m, sum);
    return EXIT_SUCCESS;
}

