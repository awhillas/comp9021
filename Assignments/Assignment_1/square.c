/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: More difficult question (1 mark)                               *
 *                                                                             *
 * Written by Alexander Whillas (z3446737)for COMP9021                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define NUMBER_OF_NUMBERS = 9

void print_solution(int []); 
int get_digit(int , int);
bool check_sqs(int []);
bool is_sq(int);
void rotate(int [], int []);
int getn(int, int);

int main(void) {
    // Hold the most relavent answer (rotated 90 counter clockwise)
    int answer[9] = {0};

    // Max/min. square root value to loop though
    int const max_sqr[9] = {3, 3, 9, 31, 99, 31, 9, 3, 3};
    int const min_sqr[9] = {0, 0, 0, 0,  32, 10, 4, 3, 3};
    int count[9] = {1};

    int level = 0;
    do {
        if (count[level] > max_sqr[level]) {
            count[level] = min_sqr[level]; // start at largest square
            level--;
            continue;   // return up one level
        }
        else {
            answer[level] = count[level] * count[level];
            count[level]++;
        }
        if (level < 8) {
            level++;
        }
        else if(check_sqs(answer)) {
            print_solution(answer);
        }
    } while (level > -1);
    
    return EXIT_SUCCESS;
}

/**
 * Check the given solution is valid or not.
 * We know they must be squares vertically, just have to check horizontally
 */ 
bool check_sqs(int in[]) {
    int rotated[4] = {0};
    rotate(in, rotated);
    for (int i = 0; i < 4; i++)
        if(!is_sq(rotated[i]) || rotated[i] == 0)
            return false;
    
    return true;
}

/**
 * Since we are working in -90 degrees from the desired output we need to rotate the answer
 * for checking and printing.
 */
void rotate(int in[9], int out[4]) {
    out[0] =  getn(in[4], 4);
    
    out[1] =  getn(in[5], 3) * 100 
            + getn(in[4], 3) * 10 
            + getn(in[3], 3);

    out[2] =  getn(in[6], 2) * 10000 
            + getn(in[5], 2) * 1000 
            + getn(in[4], 2) * 100 
            + getn(in[3], 2) * 10 
            + getn(in[2], 2);
    
    out[3] =  in[8]          * 100000000 
            + in[7]          * 10000000
            + getn(in[6], 1) * 1000000 
            + getn(in[5], 1) * 100000 
            + getn(in[4], 1) * 10000 
            + getn(in[3], 1) * 1000 
            + getn(in[2], 1) * 100
            + in[1]          * 10
            + in[0];
}

/**
 * Is the number n a perfect square?
 */ 
bool is_sq(int n) {
    int p;
    p = sqrt(n);
    return p * p == n;
}

/**
 * return the n'th digit of the number
 */
int getn(int number, int n) {
    return number / (int) pow(10, n - 1) % 10;
}

/**
 * Print a solution in the perscribed output format
 */
void print_solution(int answer[]) {
    int rotated[4] = {-1};
    rotate(answer, rotated);
    printf("%5d\n", rotated[0]);
    printf("%6d\n", rotated[1]);
    printf("%7d\n", rotated[2]);
    printf("%d\n\n", rotated[3]);
}
