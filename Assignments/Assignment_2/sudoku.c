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
// IN dexes into grid[][] global
#define VALUE 0
#define DOMAIN 1

bool get_input(void);
bool looks_ok(void);
void print_grid(void);

/* ADD FUNCTION PROTOTYPES AND GLOBAL VARIABLES */

// Track square solutions onw for VALUE and one for DOMAIN.
unsigned int grid[RANGE][RANGE][2];
// Tally of rows and columns, with the 1st element the count of numbers in that 
// row/column and then the actual numbers following that. For quick refence. The
// accounting() function fills in (updates) these arrays.
int row_tally[RANGE][RANGE + 1];
int col_tally[RANGE][RANGE + 1];
int box_tally[RANGE][RANGE + 1];

void force(void);
void mark(void);
void work(void);

// Row/Column tally management functions...
void accounting(void);
void update(int, int, int);
bool in_tally(int, int []);
void insert(int, int, int); 

unsigned int count_bits(unsigned int n);
int bit_to_number(unsigned int);

// LaTeX related output...
void latex(int);
void latex_header(void);
void latex_table(int);
void latex_footer(void);

void domain_diminution(void);
unsigned diff_all(int, int, int, int); 
void copy_tally(int [], int []);

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
            grid[i][j][DOMAIN] = !0;
    /*
    int blank[RANGE + 1] = {0};
    for (int i = 0; i < RANGE; ++i){
        copy_tally(blank, col_tally[i]);
        copy_tally(blank, row_tally[i]);
        copy_tally(blank, box_tally[i]);
    }
    accounting();
    */
    int view = 0;

    if (argc == 1) {
        if (!looks_ok())
            printf("There is clearly no solution.\n");
        else
            printf("There might be a solution.\n");
        return EXIT_SUCCESS;
    }
    if (!strcmp(argv[1], "forced") || !strcmp(argv[1], "marked") || !strcmp(argv[1], "worked")) {
        /* ADD CODE TO FIND THE FORCED DIGITS */
        force();
    }
    if (!strcmp(argv[1], "marked") || !strcmp(argv[1], "worked")) {
        /* ADD CODE TO MARK UP THE GRID */
        mark();
        view = 1;
    }
    if (!strcmp(argv[1], "worked")) {
        /* ADD CODE TO APPLY THE PREEMPTIVE SET TECHNIQUE */
        work();
        view = 2;
    }
    latex(view); // Oh YEAH!

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
            grid[i][j++][VALUE] = c - '0';
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
            unsigned int number = grid[r][c][VALUE];
            if (number == 0)
                continue;
            if(rows[r][number] || columns[c][number]) {
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
                    unsigned int number = grid[r][c][VALUE];
                    if (number == 0)
                        continue;
                    if(box[number]) {
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
                printf(" %d\n", grid[i][j][VALUE]);
            else
                printf(" %d", grid[i][j][VALUE]);
}

/* DEFINE YOUR OWN FUNCTIONS HERE ********************************************/

/**
 * Fill in the row/col_tally[] arrays
 */
void accounting(void) {
    for (int i = 0; i < RANGE; ++i) // row
        for (int j = 0; j < RANGE; ++j) // column
            if(grid[i][j][VALUE] > 0)
                update(i, j, grid[i][j][VALUE]);
}
/**
 * Given a row and column, returns a box number for indexing into the 
 * box_tally[] global. Assume row & column are zero indexed.
 */ 
int box_id(int row, int column) {
    return (row / BOX_SIZE) * (column / BOX_SIZE);
}

/**
 * Update the tallys
 */
void update(int col, int row, int value) {
    row_tally[row][++row_tally[row][0]] = value;
    col_tally[col][++col_tally[col][0]] = value;
    box_tally[box_id(row, col)][box_tally[box_id(row, col)][0]] = value;
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
 * Forced numbers should have only one cell for that number in the row/column or box
 */
void force(){
    domain_diminution();
    for (int r = 0; r < RANGE; ++r)
        for (int c = 0; c < RANGE; ++c) {
            // collected domain for row, column & box except the current cell
            unsigned int check = 0; 
            // Add row domains
            for (int i = 0; i < RANGE; ++i)
                if(i != r) 
                    check |= grid[r][i][DOMAIN]; 
            // add column domains
            for (int j = 0; j < RANGE; ++j)
                if(j != c)
                    check |= grid[j][c][DOMAIN]; // check column
            // add box domains
            for (int i = r / BOX_SIZE; i < r / BOX_SIZE + BOX_SIZE; ++i)
                for (int j = c / BOX_SIZE; j < c / BOX_SIZE + BOX_SIZE; ++j) 
                    if(i != r && j != c)
                        check |= grid[i][j][DOMAIN];
            // Subtract check domain from cell_domain
            unsigned int diff = grid[r][c][DOMAIN] & !check;
            if (count_bits(diff) == 1)
                insert(r, c, bit_to_number(diff));

        }
}

/**
 * Counts the number of bits in a int
 */
unsigned int count_bits(unsigned int n) {
    unsigned int count = 0;
    while(n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/**
 * Takes the highest bit and converts it to an int
 */
int bit_to_number(unsigned int n) {
    int count = 0;
    while(n >>= 1)
        count++;
    return count;
}

/**
 * Reduce the domains of each cell with constraint checking.
 */
void domain_diminution() {
    // Check the row and column arcs
    for (int r = 0; r < RANGE; ++r)
        for (int c = 0; c < RANGE; ++c) {
            if (grid[r][c][VALUE] > 0){
                grid[r][c][DOMAIN] = 0;
                continue;
            }
            unsigned domain = 0;
            domain |= diff_all(r, r + 1, 0, RANGE);
            domain |= diff_all(0, RANGE, c, c + 1);
            domain |= diff_all(r / BOX_SIZE, r / BOX_SIZE + BOX_SIZE, c / BOX_SIZE, c / BOX_SIZE + BOX_SIZE);
            
            grid[r][c][DOMAIN] = ~domain;
        }
}

/**
 * Insert a new number and update the tallys.
 */
void insert(int row, int col, int number) {
    grid[row][col][VALUE] = number;
}

/**
 * Checks the allDiff constraint in the given region of the grid and sets
 * the bit in the returned bitarray (unsigned int).
 */
unsigned diff_all(int row_start, int row_end, int col_start, int col_end) {
    unsigned domain = 0;
    for (int r = row_start; r < row_end; ++r)
        for (int c = col_start; c < col_end; ++c) {
            int number = grid[r][c][VALUE];
            if (number > 0)
                domain |= 1 << (number - 1);
        }
    return domain;
}

void copy_tally(int from[], int to[]) {
    for (int i = 0; i <= RANGE; ++i)
        to[i] = from[i];
}

void mark() {
    domain_diminution();
}

void work() {
    printf("work me!");
}

/**
 * Output latex representation of the grid
 */
void latex(int view) {
    latex_header();
    latex_table(view);
    latex_footer();
}

/**
 * Print the grid as a LaTeX table
 * view = 0 - bare, 1 - marked, 2 - worked
 */
void latex_table(int view) {
    for (int r = 0; r < RANGE; ++r) { // row
        printf("\n%% Line %d\n", r + 1);
        for (int c = 0; c < RANGE; ++c) { // column
            printf("\\N");
            if(view) {
                // Print the marks in the corners
                printf("{");
                unsigned domain = grid[r][c][DOMAIN];
                for (int i = 1; i <= RANGE; ++i) {
                    if (domain & 1)
                        printf("%d ", i);
                    domain >>= 1;
                    if(i % 2 == 0 && i != 8)
                        printf("}{");
                }
                printf("}");
            }
            else
                printf("{}{}{}{}");
            // Print actual value if one exists
            if (grid[r][c][VALUE] > 0)
                printf("{%d}", grid[r][c][VALUE]);
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
 
