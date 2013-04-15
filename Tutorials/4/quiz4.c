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

        if(ispunct(c)) {
            spacing_between_words = smallest_digit;
            max_nb_of_words_to_display = largest_digit;
            smallest_digit = MIN;
            largest_digit = MAX;
            if(words_displayed) {
                putchar('\n');
                words_displayed = false;
                processing_a_word = false;
            }
        } else if (isdigit(c)) {
            if (c - '0' < smallest_digit)
                smallest_digit = c -'0';
            if (c - '0' > largest_digit)
                largest_digit = c - '0';
        } 
        if (isalpha(c)) {
            // Beginning of a word
            if (max_nb_of_words_to_display > 0) {
                words_displayed = true;
                if(processing_a_word) {
                    putchar(tolower(c));
                }
                else {
                    putchar(toupper(c));
                    processing_a_word = true;
                }
            }
        } else {
            // End of a word.
            if (processing_a_word) {
                processing_a_word = false;
                max_nb_of_words_to_display--;
                for(int i = 0; i < spacing_between_words; ++i)
                    putchar(' ');
            }
        }
    }
    if (words_displayed)
        putchar('\n');
    return EXIT_SUCCESS;
}
