/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Assigns a digit to each letter that occurs in the words        *
 *              "three", "four" and "eight", distinct letters being assigned   *
 *              distinct digits, and the digit assigned to the first letter    *
 *              of each of the three words being nonzero, such that            *
 *              - three is prime,                                              *
 *              - four is a perfect square, and                                *
 *              - eight is a perfect cube.                                     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* The least possible value for nine is 1023,
 * and the square root of 1023 is 31.98.
 * The greatest possible value for nine is 9876,
 * and the square root of 9876 is 99.38. */
#define MIN_NINE 32
#define MAX_NINE 99

void copy_array(int [], int [], int); 
bool is_prime(int);

int main(void) {
    for (int x = MIN_NINE; x < MAX_NINE; x++) {
        int digits[10] = {0};
        int nine = x * x;
        // N
        
        int n = nine / 1000 % 10;
        // 'seven' is prime so 'n' can not be even
        if(n % 2 == 0) continue;
        // if the first and the 3rd digits are the same we have a valid 'n'
        if (nine / 10 % 10 != n) continue;
        digits[n] = 1;
        
        // I
        
        int i = nine / 100 % 10;
        if (++digits[i] == 2) continue;
        
        // E
        
        int e = nine % 10;
        if (++digits[e] == 2) continue;
        
        // O

        for(int o = 1; o <= 9; ++o) {
            // copy digits array
            int digits_o[10];
            copy_array(digits, digits_o, 10);

            int one = o * 100 + n * 10 + e;
            int two = one + one;
            int t = two / 100 % 10;
            int w = two / 10 % 10;
            // Check the 'o' in 'two' equals the 'o' in 'one'
            if (two % 10 != o) continue;
            // and the number hasn't been taken
            if(++digits_o[o] == 2) continue;
            if(++digits_o[t] == 2) continue;
            if(++digits_o[w] == 2) continue;

            // S

            for(int s = 1; s < 10; ++s) {
                // copy digits array
                int digits_o_s[10];
                copy_array(digits_o, digits_o_s, 10);
                
                if(++digits_o_s[s] == 2) continue;
            
                // V

                for(int v = 0; v < 10; ++v) {
                    int digits_o_s_v[10];
                    copy_array(digits_o_s, digits_o_s_v, 10);
                    if(++digits_o_s_v[v] == 2) continue;

                    int seven = s * 10000 + e * 1000 + v * 100 + e * 10 + n;
                    if(is_prime(seven)) printf("one = %d, two = %d, seven = %d and nine = %d is a solution\n", one, two, seven, nine);
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

void copy_array(int from[], int to[], int size) {
    for (int a = 0; a < size; ++a)
        to[a] = from[a];
} 

bool is_prime(int n) {
    /* Returns false if n is even. */
    if ((n % 2) == 0)
        return false;
    /* If n is not prime then it has a factor at most equal to its square root. */
    const int max = sqrt(n);
    /* Returns false if n is divisible by an odd number. */
    for (int k = 3; k <= max; k += 2) {
        if (n % k == 0)
            return false;
    }
    return true;
}
