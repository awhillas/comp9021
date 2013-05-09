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

#define RANGE 9
#define BOX_SIZE 3

bool get_input(void);
bool looks_ok(void);
void print_grid(void);

/* ADD FUNCTION PROTOTYPES AND GLOBAL VARIABLES */

// Track square solutions
int grid[RANGE][RANGE];
// track square CSP cell domains, +1 to simplify indexing. 
// true = number possible at that index
int domains[RANGE][RANGE][RANGE + 1];
// Tally of rows and columns, with the 1st element the count of numbers in that 
// row/column and then the actual numbers following that. For quick refence. The
// accounting() function fills in (updates) these arrays.
int row_tally[RANGE][RANGE + 1];
int col_tally[RANGE][RANGE + 1];

void latex();
void force();
void mark();
void work();

// Row/Column tally management functions...
void accounting(void);
void update(int, int, int);
bool in_tally(int, int []);
void add_number(int, int, int); 

// LaTeX related output...
void latex_header();
void latex_table();
void latex_footer();

void domain_diminution();
void diff_all(int , int , int , int , int []); 
void copy_domain(int [], int []);
void init_domain(int [], bool);

int main(int argc, char **argv) {
    if (argc > 2 || (argc == 2 &&
                    strcmp(argv[1], "bare") &&
                    strcmp(argv[1], "forced") &&
                    strcmp(argv[1], "marked") &&
                    strcmp(argv[1], "worked"))) {
        printf("I expect no command line argument or \"bare\", \"forced\", \"marked\" or \"worked\"\n"
               "         as unique command line argument.\n");
        return EXIT_FAILURE;
    }
    if (!get_input()) {
        printf("Incorrect input.\n");
        return EXIT_FAILURE;
    }
    
    /* POSSIBLY ADD SOME CODE HERE */
    for (int i = 0; i < RANGE; ++i)
        for (int j = 0; j < RANGE; ++j)
            init_domain(domains[i][j], 1);
    int blank[RANGE + 1] = {0};
    for (int i = 0; i < RANGE; ++i){
        copy_domain(blank, col_tally[i]);
        copy_domain(blank, row_tally[i]);
    }
    accounting();

    if (argc == 1) {
        if (!looks_ok())
            printf("There is clearly no solution.\n");
        else
            printf("There might be a solution.\n");
        return EXIT_SUCCESS;
    }
    if (!strcmp(argv[1], "forced") || !strcmp(argv[1], "marked") || !strcmp(argv[1], "worked"))
        /* ADD CODE TO FIND THE FORCED DIGITS */
        force();
    if (!strcmp(argv[1], "marked") || !strcmp(argv[1], "worked"))
        /* ADD CODE TO MARK UP THE GRID */
        mark();
    if (!strcmp(argv[1], "worked"))
        /* ADD CODE TO APPLY THE PREEMPTIVE SET TECHNIQUE */
        work();

    latex(); // Oh YEAH!

    return EXIT_SUCCESS;
}

/* DEFINE THE THREE FUNCTIONS BELOW */
bool get_input(void) {
    char c;
    int i = 0, j = 0;
    while((c = getchar()) != EOF) {
        if(c == '\n' && j) {
            if(j > 0 && j != RANGE) { // premature
                printf("i:%d, j:%d\n", i, j);
                return false;
            }
            if(j == RANGE) { // new line
                j = 0;
                i++;
            }
        }
        if(isdigit(c)) {
            grid[i][j++] = c - '0';
        }
    }
    //print_grid();
    return i == RANGE && j == 0;
}

bool looks_ok(void) {
    // Check row & columns...
    bool rows[RANGE][RANGE + 1] = {{0}};
    bool columns[RANGE][RANGE + 1] = {{0}};
    for (int r = 0; r < RANGE; ++r) // row
        for (int c = 0; c < RANGE; ++c) { // column
            int number = grid[r][c];
            if (number == 0)
                continue;
            if(rows[r][number] || columns[c][number]) {
                //printf("r:%d,c:%d,v:%d\n", r, c, number);
                return false;
            }
            else {
                rows[r][number] = true;
                columns[c][number] = true;
            }
        }
    // Check 3x3 boxes...
    for(int i = 0; i < BOX_SIZE; ++i)
        for(int j = 0; j < BOX_SIZE; ++j) {
            bool box[RANGE + 1] = {0};
            for (int r = i * BOX_SIZE; r < i * BOX_SIZE + BOX_SIZE; ++r) // row
                for (int c = j * BOX_SIZE; c < j * BOX_SIZE + BOX_SIZE; ++c) { // column
                    int number = grid[r][c];
                    if (number == 0)
                        continue;
                    if(box[number]) {
                        //printf("r:%d,c:%d,v:%d-boxie\n", r, c, number);
                        return false;
                    }
                    else
                        box[number] = true;
                }
        }

    return true;
}

void print_grid(void) {
    for (int i = 0; i < RANGE; ++i)
        for (int j = 0; j < RANGE; ++j)
            if(j == RANGE - 1)
                printf(" %d\n", grid[i][j]);
            else
                printf(" %d", grid[i][j]);
}

/* DEFINE YOUR OWN FUNCTIONS HERE */

/**
 * Fill in the row/col_tally[] arrays
 */
void accounting(void) {
    for (int i = 0; i < RANGE; ++i) // row
        for (int j = 0; j < RANGE; ++j) // column
            if(grid[i][j] > 0)
                update(i, j, grid[i][j]);
}
/**
 * UPdate the tallys
 */
void update(int col, int row, int value) {
    row_tally[col][++row_tally[col][0]] = value;
    col_tally[row][++col_tally[row][0]] = value; 
}
/**
 * Check weather a number is in a given tally
 */
bool in_tally(int number, int tally[]) {
    for (int i = 1; i <= tally[0]; ++i)
        if (tally[i] == number)
            return true;
    return false;
}

/**
 * Output latex representation of the grid
 */
void latex() {
    latex_header();
    latex_table();
    latex_footer();
}

void latex_header() {
    char header[] =
        "\\documentclass[10pt]{article}\n"
        "\\usepackage[left=0pt,right=0pt]{geometry}\n"
        "\\usepackage{tikz}\n"
        "\\usetikzlibrary{positioning}\n"
        "\\usepackage{cancel}\n"
        "\\pagestyle{empty}\n\n"
        "\\newcommand{\\N}[5]{\\tikz{\\node[label=above left:{\\tiny #1},\n"
        "                               label=above right:{\\tiny #2},\n" 
        "                               label=below left:{\\tiny #3},\n"
        "                               label=below right:{\\tiny #4}]{#5};}}\n\n"
        "\\begin{document}\n\n"
        "\\tikzset{every node/.style={minimum size=.5cm}}\n\n"
        "\\begin{center}\n"
        "\\begin{tabular}{||@{}c@{}|@{}c@{}|@{}c@{}||@{}c@{}|@{}c@{}|@{}c@{}||@{}c@{}|@{}c@{}|@{}c@{}||}\\hline\\hline"
    ;
    printf("%s", header);
}

void latex_footer() {
    char footer[] =
        "\\end{tabular}\n"
        "\\end{center}\n\n"
        "\\end{document}"
    ;
    printf("%s", footer);
}

/**
 * Print the grid as a LaTeX table
 */
void latex_table() {
    for (int r = 0; r < RANGE; ++r) { // row
        printf("\n%% Line %d\n", r + 1);
        for (int c = 0; c < RANGE; ++c) { // column
            printf("\\N");
            // Print the marks in the corners
            //int breaks[4] = {3,5,7,10};
            printf("{");
            for (int i = 1; i <= RANGE; ++i) {
                if (domains[r][c][i])
                    printf("%d ", i);
                if(i % 2 == 0 && i != 8)
                    printf("}{");
            }
            printf("}");
            // Print actual value if one exists
            if (grid[r][c] > 0)
                printf("{%d}", grid[r][c]);
            else
                printf("{}");
            // Ending(s)
            if((c + 1) % 9 != 0)
                printf(" & ");
            else
                printf(" \\\\ \\hline");
            // Double line
            if((c + 1) % 9 == 0 && (r + 1) % 3 == 0)
                printf("\\hline");
          
            if((c + 1) % 3 == 0)
                printf("\n");
        }
    }
}
void force(){}
/*
void force() {
    for (int i = 0; i < BOX_SIZE; ++i)
        for (int j = 0; j < BOX_SIZE; ++j){ 
            int free[RANGE + 1];
            init_domain(free, 1);
            int col_start = i * BOX_SIZE;
            int row_start = j * BOX_SIZE;
            diff_all(col_start, col_start + BOX_SIZE, row_start, row_start + BOX_SIZE, free);
            for (int n = 0; n < RANGE; ++n) {
                if (free[n]) {
                    int marked[BOX_SIZE][BOX_SIZE] = {{0}};
                    // Check number in each column...
                    for(int col = col_start; col < col_start + BOX_SIZE; ++col)
                        if(col_tally[col][0] && in_tally(n, col_tally[col]))
                            // mark column as used
                            for (int i = 0; i < BOX_SIZE; ++i)
                                marked[i][col] = 1;
                    // ... and in each row...
                    for(int row = row_start; row < row_start + BOX_SIZE; ++row)
                        if(col_tally[row][0] && in_tally(n, row_tally[row]))
                            for (int i = 0; i < BOX_SIZE; ++i)
                                marked[row][i] = 1;
                    // Check for an unmarked square.
                    int count = 0;
                    int row = 0;
                    int col = 0;
                    for(int col = col_start; col < col_start + BOX_SIZE; ++col)
                        for(int row = row_start; row < row_start + BOX_SIZE; ++row)
                            if (marked[col][row] == 0) {
                                row = row + row_start;
                                col = col + col_start;
                                count++;
                            }
                    if(count == 1)
                        // we have a forced number
                        add_number(row, col, n);
                }
            }
        }
}
*/
void add_number(int row, int col, int number) {

}

/**
 * Reduce the domains of each cell with constraint checking.
 */
void domain_diminution() {
    for (int row = 0; row < RANGE; ++row)
        for (int col = 0; col < RANGE; ++col) {
            if(grid[row][col] == 0) {
                int available[RANGE + 1];
                init_domain(available, true);
                diff_all(0, RANGE, col, col + 1, available); // row
                diff_all(row, row + 1, 0, RANGE, available); // column
                // region/box...
                int box_row = row / BOX_SIZE * BOX_SIZE;
                int box_col = col / BOX_SIZE * BOX_SIZE;
                diff_all(box_row, box_row + BOX_SIZE, box_col, box_col + BOX_SIZE, available); 
                copy_domain(available, domains[row][col]);
            }
            else {
                // we have a value so domain is not required.
                init_domain(domains[row][col], false);
            }
        }
}

/**
 * Checks the allDiff constraint in the given region of the grid and 
 * removes (sets to false) the option from the given domain array (from 0 to RANGE).
 */
void diff_all(int row_start, int row_end, int col_start, int col_end, int domain[]) {
    for (int r = row_start; r < row_end; ++r)
        for (int c = col_start; c < col_end; ++c) {
            int number = grid[r][c];
            if (number > 0 && domain[number]) {
                domain[number] = 0; // false
                domain[0]--;
            }
        }
}

void copy_domain(int from[], int to[]) {
    for (int i = 0; i <= RANGE; ++i)
        to[i] = from[i];
}

void init_domain(int domain[], bool value) {
    int clean[RANGE + 1];
    for(int i = 1; i <= RANGE; ++i)
        clean[i] = value;
    copy_domain(clean, domain);
    // Use the unused 0 slot as a candidate counter.
    domain[0] = RANGE * !value;
}

void mark() {
    domain_diminution();
}

void work() {
    printf("work me!");
}
