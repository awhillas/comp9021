/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: More difficult question (1 mark)                               *
 *                                                                             *
 * Written by Alexander Whillas (z3446737)for COMP9021                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MIN_ONE_DIGIT 1
#define MAX_ONE_DIGIT 10

#define MIN_THREE_DIGIT 100
#define MAX_THREE_DIGIT 999

#define MIN_FIVE_DIGIT 10000
#define MAX_FIVE_DIGIT 99999

#define MIN_NINE_DIGIT 100000000
#define MAX_NINE_DIGIT 999999999

void print_solution(int, int, int, int); 
int get_digit(int , int);
bool is_sq(int);

int main(void) {
    for(int i = MIN_ONE_DIGIT; i < MAX_ONE_DIGIT; ++i) {
        if(!is_sq(i))
           continue;

        for(int j = MIN_THREE_DIGIT; j < MAX_THREE_DIGIT; ++j) {
            if (!is_sq(j))
                continue;
        
            for(int k = MIN_FIVE_DIGIT; k < MAX_FIVE_DIGIT; ++k) {
                if (!is_sq(k))
                    continue;
                
                for(int l = MIN_NINE_DIGIT; l < MAX_NINE_DIGIT; ++l) {
                    if (!is_sq(l))
                        continue;
                    
                    // Check 2 left most digits and save ourselves some work.
                    if(!is_sq(get_digit(l, 9))) {
                        l += MIN_NINE_DIGIT;
                        continue;
                    }
                    if(!is_sq(get_digit(l, 8))) {
                        l += MIN_NINE_DIGIT / 10;
                        continue;
                    }
                    // Check 1st, 2 digit vertical
                    int vertical = get_digit(k, 5) * 10 + get_digit(l, 7);
                    if(!is_sq(vertical)) {
                        continue;
                    }
                    // check 1st 3 digit vertical
                    vertical = get_digit(j, 3) * 100 + get_digit(k, 4) * 10 + get_digit(l, 6);
                    if(!is_sq(vertical)) {
                        continue;
                    }

                    // Center vertical
                    vertical = i * 1000 + get_digit(j, 2) * 100 + get_digit(k, 3) * 10 + get_digit(l, 5);
                    if(!is_sq(vertical)) {
                        continue;
                    }
                    // check 2nd 3 digit vertical
                    vertical = get_digit(j, 1) * 100 + get_digit(k, 2) * 10 + get_digit(l, 4);
                    if(!is_sq(vertical) || get_digit(j, 1) == 0) {
                        continue;
                    }
                    // Check 2nd, 2 digit vertical
                    vertical = get_digit(k, 1) * 10 + get_digit(l, 3);
                    if(!is_sq(vertical) || get_digit(k, 1) == 0) {
                        continue;
                    }

                    // Check 2 right most digits
                    if(!is_sq(get_digit(l, 2)))
                        continue;
                    if(!is_sq(get_digit(l, 1)))
                        continue;

                    print_solution(i, j, k, l);
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Is the number n a perfect square?
 */ 
bool is_sq(int n) {
    int m;
    float p;
    p = sqrt(n);
    m = p;
    return p == m;
}

/**
 * return the n'th digit of the number
 */
int get_digit(int number, int n) {
    return number / (int) pow(10, n - 1) % 10;
}

/**
 * Print a solution in the perscribed output format
 */
void print_solution(int one, int three, int five, int nine) {
    printf("%5d\n", one);
    printf("%6d\n", three);
    printf("%7d\n", five);
    printf("%d\n\n", nine);
}
