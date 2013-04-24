/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
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
        if (isspace(c) || isdigit(c)) {
            if (processing_a_word) {
                processing_a_word = false;
                max_nb_of_words_to_display ? --max_nb_of_words_to_display : 0;
            }
            if (isdigit(c)) {
                if (c - '0' > largest_digit)
                    largest_digit = c - '0';
                if (c - '0' < smallest_digit)
                    smallest_digit = c - '0';
            }
            continue;
        }
        if (!isalpha(c)) {
            if (words_displayed) {
                putchar('\n');
                words_displayed = false;
            }
            processing_a_word = false;
            words_displayed = false;
            spacing_between_words = smallest_digit;
            max_nb_of_words_to_display = largest_digit;
            smallest_digit = MIN;
            largest_digit = MAX;
            continue;
        }
        if (max_nb_of_words_to_display) {
            if (!processing_a_word) {
                processing_a_word = true;
                if (words_displayed)
                    for (int i = 0; i < spacing_between_words; ++i)
                        putchar(' ');
                putchar(toupper(c));
            }
            else
                putchar(tolower(c));
            words_displayed = true;
        }
    }
    if (words_displayed)
        putchar('\n');
    return EXIT_SUCCESS;
}

