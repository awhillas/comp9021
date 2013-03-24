/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *                                                                             *
 * By Alexander Whillas (z3446737) for COMP9021.                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void getPrimes(int, int*);

int main(int argc, char **argv) {
    /* We run the program with one number as command line argument. */
    if (argc != 2) {
        printf("Please provide 1 command line argument.\n");
        return EXIT_FAILURE;
    }
    int number = atoi(argv[1]);
    int* primes[number + 1];
    getPrimes(number, primes);
    int lpf = number; // Lowest Prime Factor
    while(primes[lpf] != 1) {
        lpf--;
    }
    
    printf("A solution is %d", lpf);
    return EXIT_SUCCESS;
}

/**
 * Sieve of Eratosthenes
 */ 
void getPrimes(int limit, int* numbers) {
    // Initialise...
    //int numbers[limit + 1]; // ignore 0 & 1
    for(int i = 0; i < limit; ++i)
        numbers[i] = 1;
    // Main loop...
    int p = 2; // 1st prime
    while(p < limit) {
        int multiplier = 2;
        // Eliminate multipules of the prime
        while(p * multiplier < limit) {
            numbers[p * multiplier] = 0; // mark as not-prime
            multiplier++;
        }
        // find the next prime within limit
        while(p < limit && numbers[++p] != 0)
            ;
    }
}

    
