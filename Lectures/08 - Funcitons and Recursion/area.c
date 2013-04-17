/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Gets from standard input the representation of a region        *
 *              made up of 0's (representing free spaces) and 1's              *
 *              (representing obstacles). The region has a height of 6 and a   *
 *              width of 10. Successive digits are separated by one space      *
 *              character.                                                     *
 *              In practice, the input is stored in a file whose contents is   *
 *              redirected to standard input.                                  *
 *              Computes the largest free area, defined as a maximal set of    *
 *              0's such that it is possible to go from from any 0 to any      *
 *              other 0 in the region by moving vertically or horizontally     *
 *              (but not diagonally).                                          *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define NB_OF_ROWS 6
#define NB_OF_COLUMNS 10

int data[NB_OF_ROWS][NB_OF_COLUMNS];

void read_data(void);
int compute_area(int, int);

int main(void) {
    read_data();
    int max_area = 0;
    int area;
    for (int i = 0; i < NB_OF_ROWS; ++i)
        for (int j = 0; j < NB_OF_COLUMNS; ++j) {
            /* We are somewhere in some free space we have not explored yet. */
            if (data[i][j] == 0) {
                area = compute_area(i, j);
                if (area > max_area)
                    max_area = area;
            }
        }
    printf("Max area: %d\n", max_area);
    return EXIT_SUCCESS;
}

void read_data(void) {
    for (int i = 0; i < NB_OF_ROWS; ++i)
        for (int j = 0; j < NB_OF_COLUMNS; ++j) {
            if (getchar() == '1')
                data[i][j] = 1;
            /* Eat up space or new line character after the digit
             * that has just been read. */
            getchar();
        }
}

int compute_area(int i, int j) {
    /* We are outside the region or not in some free space. */
    if (i < 0 ||
        i >= NB_OF_ROWS ||
        j < 0 ||
        j >= NB_OF_COLUMNS ||
        data[i][j] == 1)
        return 0;
    /* We do not want to go back here and think we have discovered
     * some new free space. */
    data[i][j] = 1;
    /* We are in a free space that consists of a cell possibly connected with
     * some extra free space that is located north, south, west or east of that cell. */
    return 1 +
        compute_area(i - 1, j) +
        compute_area(i + 1, j) +
        compute_area(i, j - 1) +
        compute_area(i, j + 1);
}


