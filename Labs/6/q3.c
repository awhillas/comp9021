/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Calculate the GCD of 2 integers. See p.173 of Ross & Wright    *
 *                                                                             *
 * Written by ALexander Whillas z3446737 for COMP9021                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int find_solutions(int, unsigned long long);

int main(void) {
    unsigned long long digits = 0; 
    int sum = 0, solutions = 0;
    
    printf("Input an unsigned long long and an int: ");
    scanf("%llu %d", &digits, &sum);
    
    solutions = find_solutions(sum, digits);

    if (solutions == 0)
        printf("There is no solution.\n");
    else if (solutions == 1)
        printf("There is a unique solution\n");
    else
        printf("There are %d solutions.\n", solutions);
    
    return EXIT_SUCCESS;
}

int find_solutions(int target_sum, unsigned long long digits) {
    int count = 0;
    while(digits % 10) {
        int const n = digits % 10;
        digits /= 10;
        
        if (n < target_sum)
            count += find_solutions(target_sum - n, digits);
        else if (n == target_sum)
            count++;
    }
    return count;
}
