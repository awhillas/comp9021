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
// Indexes into grid[][][] global
#define VALUE 0
#define DOMAIN 1
#define CROSSED 2
// Constants for where we are searching. See *_preemptive_set()
#define ROW 0
#define COLUMN 1
#define BOX 2

bool get_input(void);
bool looks_ok(void);
void print_grid(void);

/* ADD FUNCTION PROTOTYPES AND GLOBAL VARIABLES */

// Track cell VALUE, DOMAIN and WORKED domain
unsigned grid[RANGE][RANGE][3];
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
void tally_accounting(void);
void update_tallys(int, int);
void insert(int, int, int); 

unsigned count_bits(unsigned n);
int bit_to_number(unsigned);

// LaTeX related output...
void latex(int);
void latex_header(void);
void latex_table(int);
void latex_footer(void);

void domain_diminution(void);
unsigned get_numbers(int, int, int, int); 
bool seek_preemptive_set(int , int [RANGE][RANGE + 1]);

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
        for (int j = 0; j < RANGE; ++j) {
            grid[i][j][DOMAIN] = !0;
            grid[i][j][CROSSED] = 0;
        }
    // Default view is "bare"
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
            unsigned number = grid[r][c][VALUE];
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
                    unsigned number = grid[r][c][VALUE];
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
 * Fill in the row/col/box_tally[] arrays which track the empty cells in each.
 */
void tally_accounting(void) {
    for (int i = 0; i < RANGE; ++i) // row
        for (int j = 0; j < RANGE; ++j) // column
            if(grid[i][j][VALUE] == 0)
                update_tallys(i, j);
}
/**
 * Given a row and column, returns a box number for indexing into the 
 * box_tally[] global. Assume row & column are zero indexed.
 */ 
int box_id(int row, int column) {
    return (row / BOX_SIZE * BOX_SIZE) + (column / BOX_SIZE);
}

/**
 * Update the tallys of empty cells
 */
void update_tallys(int row, int col) {
    row_tally[row][++row_tally[row][0]] = col;
    col_tally[col][++col_tally[col][0]] = row;
    box_tally[box_id(row, col)][box_tally[box_id(row, col)][0]] = row * BOX_SIZE + col;
}

/**
 * Forced numbers should have only one cell for that number in the row/column or box
 */
void force() {
    bool found_forced_cells = false;
    domain_diminution();
    for (int r = 0; r < RANGE; ++r)
        for (int c = 0; c < RANGE; ++c) {
            // collected domain for current box except for the current cell
            unsigned check = 0; 
            // add box domains
            int row_start = r / BOX_SIZE * BOX_SIZE;
            int col_start = c / BOX_SIZE * BOX_SIZE;
            for (int i = row_start; i < row_start + BOX_SIZE; ++i)
                for (int j = col_start; j < col_start + BOX_SIZE; ++j)
                    if(i != r || j != c)
                        check |= grid[i][j][DOMAIN];
            // Subtract check domain from cell_domain
            unsigned diff = grid[r][c][DOMAIN] & ~check;
            if (count_bits(diff) == 1) {
                found_forced_cells = true;
                insert(r, c, bit_to_number(diff));
            }
        }
    if(found_forced_cells)
        force();
}
/**
 * Insert a new number and update the tallys.
 */
void insert(int row, int col, int number) {
    grid[row][col][VALUE] = number;
}
/**
 * Counts the number of 1's in the first RANGE bits 
 */
unsigned count_bits(unsigned n) {
    int count = 0;
    for(int i = 0; i < RANGE; ++i)
        if(n & 1 << i)
            count++;
    return count;
}
/**
 * Takes the highest bit and converts it to an int
 */
int bit_to_number(unsigned n) {
    for(int i = 0; i < RANGE; ++i)
        if(n & 1 << i)
            return i + 1;
    return 0;
}

/**
 * Reduce the domains of each cell with constraint checking.
 * Each domain is refreshed.
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
            domain |= get_numbers(r, r + 1, 0, RANGE);
            domain |= get_numbers(0, RANGE, c, c + 1);
            int row_start = r / BOX_SIZE * BOX_SIZE;
            int col_start = c / BOX_SIZE * BOX_SIZE;
            domain |= get_numbers(row_start, row_start + BOX_SIZE, col_start, col_start + BOX_SIZE);
            // Inver the result as the domain marks the avaiable number not the 
            // unavaiable.
            grid[r][c][DOMAIN] = ~domain;
        }
}
/**
 * Gets the numbers in the given region.
 */
unsigned get_numbers(int row_start, int row_end, int col_start, int col_end) {
    unsigned domain = 0;
    for (int r = row_start; r < row_end; ++r)
        for (int c = col_start; c < col_end; ++c) {
            int number = grid[r][c][VALUE];
            if (number > 0)
                domain |= 1 << (number - 1);
        }
    return domain;
}

void mark() {
    domain_diminution();
}

/**
 * Remove the given bits from the domain and move to the CROSSED out domain
 */
void cross_out(int row, int col, unsigned preemptive_set) {
    grid[row][col][CROSSED] |= grid[row][col][DOMAIN] & preemptive_set;  // add
    grid[row][col][DOMAIN] &= ~preemptive_set;  // remove
}

/**
 * Look for a premptive set with the given numbers
 */ 
bool check_preemptive_set(unsigned preemptive_set, int what, int where) {
    bool set_found = false;
    int size = count_bits(preemptive_set);
    if (size) {
        int row_start = 0;
        int row_end = RANGE;
        int col_start = 0;
        int col_end = RANGE;
        switch(what) {
            case BOX:
                // in the case of BOX, 'where' is a box_id
                row_start = where / BOX_SIZE * BOX_SIZE;
                row_end = row_start + BOX_SIZE;
                col_start = where % BOX_SIZE * BOX_SIZE;
                col_end = col_start + BOX_SIZE;
                break;
            case ROW:
                row_start = where;
                row_end = where + 1;
                break;
            case COLUMN:
                col_start = where;
                col_end = where + 1;
        }
        // Check all bits within the preemptive set & that we have the right amount of cells.
        int count = 0;
        for (int r = row_start; r < row_end; ++r)
            for (int c = col_start; c < col_end; ++c)
                if(grid[r][c][VALUE] == 0)
                    if(count_bits(grid[r][c][DOMAIN] & ~preemptive_set) == 0) 
                        count++;
        if (count == size)
            // We found one! so remove from cells not in the set
            for (int r = row_start; r < row_end; ++r)
                for (int c = col_start; c < col_end; ++c)
                    if(grid[r][c][VALUE] == 0 && (grid[r][c][DOMAIN] & ~preemptive_set)) {
                        cross_out(r, c, preemptive_set);
                        set_found = true;
                        // We found a singleton!
                        if(count_bits(grid[r][c][DOMAIN]) == 1) {
                            insert(r, c, bit_to_number(grid[r][c][DOMAIN]));
                            cross_out(r, c, grid[r][c][DOMAIN]);
                        }
                    }
    }
    return set_found;
}

/**
 * Recurvily build a Power Set, of all elements of length k, from the the bits in 
 * the domain set. These will be our preemptive sets.
 * What is one of ROW, COLUMN or BOX constants.
 * Where is the number coresponding to those constants.
 * Returns true if a pre-emptive set is found, false otherwise.
 */
bool build_preemptive_sets(unsigned domain, unsigned element, int k, int what, int where) {
    bool result = false;
    if(k > 0) {
        unsigned available_bits = domain;
        // Find next bit
        int i = 0;
        while (i <= RANGE) {
            if(available_bits & 1) {
                domain ^= 1 << i;  // remove bit
                result |= build_preemptive_sets(domain, element | 1 << i, k - 1, what, where);
            }
            available_bits >>= 1;
            i++;
        }
    }
    else
        // Reached the premtive set size we are after so use it!
        return check_preemptive_set(element, what, where);

    return result;
}

unsigned get_total_domain(int tally[RANGE + 1]) {
    unsigned domain = 0;
    for(int x = 1; x <= tally[0]; ++x)
        domain |= grid[x][tally[x]][DOMAIN];
    return domain;
}

/**
 * Loop thought an empty cell tally and check for preemptive sets in rows, columns and boxes
 */
bool seek_preemptive_set(int what, int tallys[RANGE][RANGE + 1]) {
    bool set_found = false;
    for (int i = 0; i < RANGE; ++i) {
        int number_of_empties = tallys[i][0];
        //if(number_of_empties > 2 && number_of_empties < 9) {
            for(int size = 2; size <= number_of_empties - 1; ++size)
                set_found = build_preemptive_sets(get_total_domain(tallys[i]), 0, size, what, i);
        //}
    }
    return set_found;
}

void work() {
    tally_accounting();
    bool found = false;
    found |= seek_preemptive_set(ROW, row_tally);
    found |= seek_preemptive_set(COLUMN, col_tally); 
    found |= seek_preemptive_set(BOX, box_tally);
    if(found) {
        // TODO:
        // Check for forced.
        // Check if we have solved it.
        work(); // again!
    }
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
                unsigned crossed = grid[r][c][CROSSED];
                for (int i = 1; i <= RANGE; ++i) {
                    if (domain & 1)
                        printf("%d ", i);
                    if (crossed & 1)
                        printf("\\cancel{%d} ", i);
                    domain >>= 1;
                    crossed >>= 1;
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
        "\\begin{tabular}{||@{}c@{}|@{}c@{}|@{}c@{}||@{}c@{}|@{}c@{}|@{}c@{}||@{}c@{}|@{}c@{}|@{}c@{}||}\\hline\\hline";
    printf("%s", header);
}

void latex_footer() {
    char footer[] =
        "\\end{tabular}\n"
        "\\end{center}\n\n"
        "\\end{document}";
    printf("%s", footer);
}
 
