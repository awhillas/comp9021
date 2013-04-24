/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 10

bool grid[DIM][DIM];

void display_grid(void);
/* Returns an integer n such that n % 100 is the width and n / 100 the height
 * of the widest largest rectangle made up of 1s in the grid. */
int dimensions_of_largest_rectangle(void);
/* If j1 <= j2 and the grid has a 1 at the intersection of row i and column j
 * for all j in {j1, ..., j2}, then returns the height of the heighest rectangle
 * whose top border is made up of those 1s. */
int height_of_rectangle_with_given_top_border(int i, int j1, int j2);

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
            grid[i][j] = rand() % nb_of_possible_outcomes;
    puts("Here is the grid that has been generated:\n");
    display_grid();
    int size = dimensions_of_largest_rectangle();
    printf("The widest largest rectangle made up of 1s in the grid\n"
           "(so we maximise the area, and THEN we maximise the width)\n"
           "has a size of %d x %d\n",
           size % 100, size / 100);    
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

/* Returns an integer n such that n % 100 is the width and n / 100 the height
 * of the widest largest rectangle made up of 1s in the grid. */
int dimensions_of_largest_rectangle(void) {
    /* REPLACE COMMENT WITH YOUR CODE */
    int height, width, area, tallest, longest;
    tallest = longest = 0;
    for (int i = 0; i < DIM; ++i) {
        for (int j1 = 0; j1 < DIM; ++j1) {
            if(grid[i][j1])
                for (int j2 = j1; j2 < DIM; ++j2) {
                    if (grid[i][j2]) {
                        height = height_of_rectangle_with_given_top_border(i, j1, j2);
                        width = j2 - j1 + 1;
                        area = height * width;
                        if(area > tallest * longest) {
                            tallest = height;
                            longest = width;
                        } 
                        else if (area == tallest * longest && width > longest) {
                            tallest = height;
                            longest = width;
                        }
                    }
                    else
                        break;
                }
        }
    }
    return tallest * 100 + longest;
}

/* If j1 <= j2 and the grid has a 1 at the intersection of row i and column j
 * for all j in {j1, ..., j2}, then returns the height of the heighest rectangle
 * whose top border is made up of those 1s. */
int height_of_rectangle_with_given_top_border(int i, int j1, int j2) {
     /* REPLACE COMMENT WITH YOUR CODE */
    // Check we have all 1's on this row between the given columns
    for (int col = j1; col <= j2; ++col)
        if (!grid[i][col])
            return 0;
    // If we do then check the next one...
    return height_of_rectangle_with_given_top_border(i + 1, j1, j2) + 1;
}

