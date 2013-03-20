/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define BOUND 10

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
    int second_smallest_number = BOUND;
    int smallest_number = data[0];
    for (int i = 1; i < SIZE; ++i) {
        if (data[i] < smallest_number) {
            third_smallest_number = second_smallest_number;
            second_smallest_number = smallest_number;
            smallest_number = data[i];
        }
        else if (data[i] > smallest_number && data[i] < second_smallest_number) {
            third_smallest_number = second_smallest_number;
            second_smallest_number = data[i];
        }
        else if (data[i] > second_smallest_number && data[i] < third_smallest_number)
            third_smallest_number = data[i];
    }
    for (int i = 0; i < SIZE; ++i)
        printf("%4d", data[i]);
    if (third_smallest_number == BOUND)
        printf("\n  does not contain three distinct numbers.\n");
    else
        printf("\n  has %d as third smallest number.\n", third_smallest_number);
    return EXIT_SUCCESS;
}
