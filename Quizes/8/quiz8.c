/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_word(FILE *const, FILE *const, long, long);

int main(void) {
    FILE *const input_file = fopen("input.txt", "r");
    if (!input_file) {
        printf("Please create a file named \"input.txt\""
               " in the working directory.\n");
        return EXIT_FAILURE;
    }
    FILE *const output_file = fopen("output.txt", "w");
   
    /* REPLACE THIS COMMENT WITH YOUR CODE */
    long fwd_head = 0;
    long rev_head = 1;
    long dir = 1;   // 1 = forward, -1 = reverse;
    fseek(input_file, 0, SEEK_END);
    long size = ftell(input_file);
    bool in_word = false;
    long start_of_word = 0; 
    while ((fwd_head + rev_head - 1) < size) {
        if(dir == 1) {
            // forward
            fseek(input_file, fwd_head++, SEEK_SET);
        }
        else {
            // backwards
            fseek(input_file, -rev_head++, SEEK_END);
        }
        char c = getc(input_file);
        if(isalpha(c)) {
            if (dir == -1) {
                if(!in_word)
                    start_of_word = rev_head - 1;
            }
            else
                putc(c, output_file);
            in_word = true;
        }
        else {
            if (in_word) {
                in_word = false;
                if (dir == -1) {
                    print_word(input_file, output_file, size - rev_head + 2, size - start_of_word + 1);
                    dir = 1;
                }
                else
                    dir = -1;
                putc('\n', output_file);
            }
        }
    }

    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}

void print_word(FILE *const input_file, FILE * const output_file, long start, long end) {
    for(int i = start; i < end; ++i) {
        fseek(input_file, i, SEEK_SET);
        putc(getc(input_file), output_file);
    }
}
