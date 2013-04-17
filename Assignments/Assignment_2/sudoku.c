/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Makes progress on a sudoku puzzle using the forced digits and  *
 *              preemptive set techniques described in the paper               *
 *              A Pencil-and-Paper Algorithm for Solving Sudoku Puzzles        *
 *              by J. F. Crook, Notices of the AMS, 56(4), pp. 460--468.       *
 *                                                                             *
 *              The program  expects either no command line argument or        *
 *              "bare", "forced", "marked" or "worked" as single command line  *
 *              argument. It reads input from standard input (in practice,     *
 *              the contents of a .txt file redirected to standard input),     *
 *              meant to consist of 9 lines of 9 digits, with possibly lines   *
 *              consisting of spaces only that will be ignored and with        *
 *              possibly spaces anywhere on the lines with digits, intended    *
 *              to represent a suduku grid.                                    *
 *                                                                             *
 *              When there is no command line argument, the program checks     *
 *              whether there might be a solution, in the sense that no row,   *
 *              column or box contains twice the same digit. The program is    *
 *              meant to be run with one of the 4 possible command line        *
 *              arguments only is there might be a solution.                   *
 *                                                                             *
 *              When the command line argument is "bare", the program outputs  *
 *              some .tex code meant to be redirected to a file and compiled   *
 *              with pdflatex to yield a pictorial representation of the grid. *
 *                                                                             *
 *              When the command line argument is "forced", the program        *
 *              determines all forced digits, that is, all digits that must    *
 *              fill an empty cell in a box because that box does not contain  *
 *              that digit yet and all other empty cells in that box are       *
 *              on a row or on a column that contains that digit. As forced    *
 *              digits are being discovered and fill empty cells, more forced  *
 *              digits might be discovered that could not be discovered        *
 *              in the first round. When all forced digits have eventually     *
 *              been discovered, the program outputs some .tex code meant      *
 *              to be redirected to a file and compiled with pdflatex to yield *
 *              a pictorial representation of the original grid with the       *
 *              forced digits added.                                           *
 *                                                                             *
 *              When the command line argument is "marked", the program        *
 *              determines the forced digits and outputs some .tex code meant  *
 *              to be redirected to a file and compiled with pdflatex to yield *
 *              a pictorial representation of the grid with the forced digits  *
 *              added and with all empty cells marked with the digits that can *
 *              possibly fill that cell, namely, the digits that do not occur  *
 *              on the same row, on the same column or in the same box.        *
 *                                                                             *
 *              When the command line argument is "worked", the program        *
 *              determines the forced digits and outputs some .tex code meant  *
 *              to be redirected to a file and compiled with pdflatex to yield *
 *              a pictorial representation of the grid with the forced digits  *
 *              added, with all empty cells marked, and with the preemptive    *
 *              set technique applied until it cannot allow one to eliminate   *
 *              any possible digit from any cell (which might be because the   *
 *              puzzle has been solved).                                       *
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool get_input(void);
bool looks_ok(void);
void print_grid(void);
/* ADD FUNCTION PROTOTYPES AND GLOBAL VARIABLES */

int main(int argc, char **argv) {
    if (argc > 2 || argc == 2 &&
                    strcmp(argv[1], "bare") &&
                    strcmp(argv[1], "forced") &&
                    strcmp(argv[1], "marked") &&
                    strcmp(argv[1], "worked")) {
        printf("I expect no command line argument or \"bare\", \"forced\", \"marked\" or \"worked\"\n"
               "         as unique command line argument.\n");
        return EXIT_FAILURE;
    }
    if (!get_input()) {
        printf("Incorrect input.\n");
        return EXIT_FAILURE;
    }
    /* POSSIBLY ADD SOME CODE HERE */
    if (argc == 1) {
        if (!looks_ok())
            printf("There is clearly no solution.\n");
        else
            printf("There might be a solution.\n");
        return EXIT_SUCCESS;
    }
    if (!strcmp(argv[1], "forced") || !strcmp(argv[1], "marked") || !strcmp(argv[1], "worked"))
        /* ADD CODE TO FIND THE FORCED DIGITS */
    if (!strcmp(argv[1], "marked") || !strcmp(argv[1], "worked"))
        /* ADD CODE TO MARK UP THE GRID */
    if (!strcmp(argv[1], "worked"))
        /* ADD CODE TO APPLY THE PREEMPTIVE SET TECHNIQUE */
    print_grid();
    return EXIT_SUCCESS;
}

/* DEFINE THE THREE FUNCTIONS BELOW */
bool get_input(void) {
}

bool looks_ok(void) {
}

void print_grid(void) {
}

/* DEFINE YOUR OWN FUNCTIONS HERE */
