/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all multiplications of the form                          *
 *                            *  *  *                                          *
 *                        x   *  *  *                                          *
 *                            -------                                          *
 *                         *  *  *  *                                          *
 *                      *  *  *  *                                             *
 *                   *  *  *  *                                                *
 *                   ----------------                                          *
 *                   *  *  *  *  *  *                                          *
 *              that satisfy the following conditions:                         *
 *              - each star stands for a digit, with the leftmost star         *
 *                on each line standing for a nonzero digit;                   *
 *              - all partial products are made up of the same digits;         *
 *              - the first and second partial products are different;         *
 *              - the orderings of digits in the second and third              *
 *                partial products are inverse of each other;                  *
 *              - the third partial product is the sum of the first two        *
 *                partial products.                                            *
 *                                                                             *
 * Written by Alexander Whillas (z3446737) for COMP902                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool digits_unique(int, int []);

bool only_certain_digits(int [], int, int);

int main(void) {
    for (int m = 100; m < 10000; ++m)
        for (int n = 100; n < 1000; ++n) {
            int product = m * n;
            if (product < 1000000)
                continue;

//            printf("%d\n", product);
            
            int digits[10] = {0};
            if(!digits_unique(m, digits))
                continue;
            if(!only_certain_digits(digits, n, 3))
                continue;
            if(!only_certain_digits(digits, product, 7))
                continue;

            // Get the partial products
            int partial_product1 = m * (n % 10);
            if (partial_product1 < 10000)
                continue;
            if(!only_certain_digits(digits, partial_product1, 5))
                continue;

            int partial_product2 = m * (n / 10 % 10);
            if (partial_product2 < 10000)
                continue;
            if(!only_certain_digits(digits, partial_product2, 5))
                continue;
            
            int partial_product3 = m * (n / 100);
            if (partial_product3 < 1000)
                continue;
            if(!only_certain_digits(digits, partial_product3, 4))
                continue;

//for(int i = 0; i < 10; ++i) {printf("%d ", digits[i]);} printf("\n");
            printf("%7d\n  x%4d\n", m, n);
            printf("   ----\n");
            printf("%7d\n%6d\n%5d\n", partial_product1, partial_product2, partial_product3);
            printf("-------\n");
            printf("%d\n", product);
        }
    return EXIT_SUCCESS;
}

/**
 * Check the digits are unique.
 * Keep the found digits in the digits[] for later
 */ 
bool digits_unique(int n, int digits[]) {
    bool unique = true; // is it?
    for(int i = 1000; i >= 1; i /= 10) {
        int d = n / i % 10;
        if(digits[d] == 0)
            digits[d]++;
        else
            unique = false;
    }
    return unique;
}

/**
 * Determine if n only contains digits[]
 */
bool only_certain_digits(int digits[], int n, int length) {
    for(int i = (int) pow(10, length - 1); i >= 1; i /= 10) {
        int d = n / i % 10;
        if(digits[d] == 0)
            return false;
    }
    return true;
}
