/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Calculate the GCD of 2 integers. See p.173 of Ross & Wright    *
 *                                                                             *
 * Written by ALexander Whillas z3446737 for COMP9021                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int m, n, a, b;
    
    printf("Input two integers:");
    scanf("%d %d", &m, &n);
    
    a = m;
    b = n;

    // The pairs (a,b) and (m,n) have the same GCD
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    printf("The gcd of %d and %d is %d.\n", m, n, a);
    return EXIT_SUCCESS;
}
