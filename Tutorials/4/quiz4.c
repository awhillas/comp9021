/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN 9 // min(emptyset) = 9 as the largest lower bound
#define MAX 0 // max(emptyset) = 0 as the smallest upper bound

int main(void) {
    int smallest_digit = MIN; 
    int largest_digit = MAX; 
    bool processing_a_word = false;
    bool words_displayed = false;
    int spacing_between_words = smallest_digit;
    int max_nb_of_words_to_display = largest_digit;
    int c;
    while ((c = getchar()) != '\n') {
        /* REPLACE THIS COMMENT WITH YOUR CODE */
    }
    if (words_displayed)
        putchar('\n');
    return EXIT_SUCCESS;
}
