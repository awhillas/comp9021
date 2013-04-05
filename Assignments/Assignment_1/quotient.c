/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all fractions of the form n/m sucha that n and d are     *
 *              positive integers with no occurrence of zero, n/d evaluates to *
 *              0.5, and every nonzero digit occurs once and only once in n or *
 *              d.                                                             *
 *                                                                             *
 * Written by Alexander Whillas (z3446737) for COMP9021                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Maximum multiplicand
#define MAX 9876

bool digits_unique(int, int []);

int main(void) {
    for (int i = 1; i < MAX; ++i) {
        int digits[10] = {0}; 
        if(digits_unique(i, digits) && digits_unique(i * 2, digits))
            printf("%d / %d = 0.5\n", i, i * 2);
        
    }
    return EXIT_SUCCESS;
}

/**
 * Check the digits are unique and non-zero!
 * Keep the found digits in digits[] for future reference.
 */ 
bool digits_unique(int n, int digits[]) {
    while(n >= 1) {
        int d = n % 10;
        if(digits[d] == 0 && d != 0)
            digits[d]++;
        else
            return false;
        n /= 10;
    }
    return true;
}
