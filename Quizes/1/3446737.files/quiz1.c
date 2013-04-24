/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Quiz 1
 *                                                                             *
 * Written by Alexander Whillas (z3446737) for COMP9021                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define BOUND 10
#define LENGTH(x) (sizeof(x)/sizeof(*(x)))

int main(int argc, char **argv) {
    /* We run the program with one number as command line argument. */
    if (argc != 2) {
        printf("Please provide 1 command line argument.\n");
        return EXIT_FAILURE;
    }
    /* We use it as a seed for the random number generator. */
    srand(strtoul(argv[1], NULL, 10));
    int data[SIZE];
    /* We randomly generate 10 numbers in the range [0, 10) and store them in data. */
    for (int i = 0; i < SIZE; ++i)
        data[i] = rand() % BOUND;
    int third_smallest_number = BOUND;
    
    /* Variation on Nonlinear General Selection algorithum */
    int k = 3; // 3rd smallest.
    int list[k];
    int lastMinValue = -1;
    for (int i = 0; i < k; ++i) {
        int minValue = BOUND;
        for (int j = 0; j < SIZE; ++j) {
            if (data[j] > lastMinValue && data[j] < minValue) {
                minValue = data[j];
            }
        }
        list[i] = minValue;
        lastMinValue = minValue;
    }
    if(LENGTH(list) >= k)
        third_smallest_number = list[k - 1];

    for (int i = 0; i < SIZE; ++i)
        printf("%4d", data[i]);
    if (third_smallest_number == BOUND)
        printf("\n  does not contain three distinct numbers.\n");
    else
        printf("\n  has %d as third smallest number.\n", third_smallest_number);
    return EXIT_SUCCESS;
}

