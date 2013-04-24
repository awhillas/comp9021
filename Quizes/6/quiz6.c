/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 10

int grid[DIM][DIM];

void display_grid(void);
/* Returns the size of the largest connected region which has a checkers-like structure,
 * starting the exploration from the point of coordinates (i, j). */
int explore_from(int i, int j);

int main(int argc, char **argv) {
    /* We run the program with two command line arguments. */
    if (argc != 3) {
        printf("Please provide 2 command line arguments.\n");
        return EXIT_FAILURE;
    }
    /* The first one will determine our probability distribution;
     * it is meant to be strictly positive. */
    int nb_of_possible_outcomes = strtol(argv[1], NULL, 10);
    /* We use the second command line argument, meant to be a nonnegative integer,
     * as a seed for the random number generator. */
    srand(strtoul(argv[2], NULL, 10));
    /* We fill the grid with randomly generated 0s and 1s,
     * with for every cell, a probability of 1/nb_of_possible_outcomes to generate a 0. */
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            grid[i][j] = (bool)(rand() % nb_of_possible_outcomes);
    puts("Here is the grid that has been generated:\n");
    display_grid();
    int max_size_of_region_with_checkers_structure = 0;
    /* REPLACE WITH COMMENT WITH YOUR CODE */
    printf("The size of the largest area with a checkers structure is %d\n",
           max_size_of_region_with_checkers_structure);    
    return EXIT_SUCCESS;
}

void display_grid(void) {
    for (int i = 0; i < DIM; ++i) {
        printf("    ");
        for (int j = 0; j < DIM; ++j)
            grid[i][j] ? printf(" 1") : printf(" 0");
        putchar('\n');
    }
    putchar('\n');
}

int explore_from(int i, int j) {
    /* REPLACE WITH COMMENT WITH YOUR CODE */
}



            

