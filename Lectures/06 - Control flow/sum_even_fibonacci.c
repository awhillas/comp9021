/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Computes the sum of all even Fibonacci numbers                 *
 *              that are at most equal to some value provided by the user.     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <p_io.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    unsigned long long bound;
    p_prompt("Enter an integer at least equal to 2: ", "%>=2llu", &bound);
    /* t1 and t2 and penultimate and last computed terms
     * in the Fibonacci sequence. */
    unsigned long long t1 = 1, t2 = 2;
    unsigned long long t1_plus_t2;
    unsigned long long sum = 0;
    while (t2 <= bound) {
        sum += t2;
        /* Precisely every third term in the Fibonacci sequence is even,
         * so the updated value for t1 is t2 + (t1 + t2),
         * and the updated value for t2 is (t1 + t2) + (t2 + (t1 + t2)). */
        t1_plus_t2 = t1 + t2;
        t1 = t2 + t1_plus_t2;
        t2 = t1 + t1_plus_t2;
    }
    printf("The sum of all even Fibonacci numbers at most equal to %llu is %llu\n", bound, sum);
    return EXIT_SUCCESS;
}
