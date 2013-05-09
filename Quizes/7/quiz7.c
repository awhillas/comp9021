/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_OF_ARGS 10

void copy_array(char* [], char* [], int);
void clean(char*);

int main(int argc, char* argv[]) {
    if (argc != NB_OF_ARGS + 1) {
        printf("Run the program with 10 command line arguments please.\n");
        return EXIT_FAILURE;
    }
    
    /* REPLACE WITH COMMENT WITH YOUR CODE */
    char* copy[NB_OF_ARGS + 1];
    copy_array(argv, copy, NB_OF_ARGS);
    // Reagrange words based on first digit, if any found in them.
    for (int w = 1; w <= NB_OF_ARGS; ++w) {
        int j = 0;
        char c;
        while((c = copy[w][j++])) {
            if(isdigit(c)) {
                int word_index = c - '0';
                if(word_index == 0)
                    word_index = 10;
                copy[w] = argv[word_index];
                break;
            }
        }
    }
    for (int w = 1; w <= NB_OF_ARGS; ++w)
        clean(copy[w]);
    
    for (int i = 1; i <= NB_OF_ARGS; ++i)
        printf("  %s", copy[i]);
    putchar('\n');
    return EXIT_SUCCESS;
}

// Copy one char* array into another
void copy_array(char* from[], char* to[], int size) {
    for (int w = 1; w <= size; ++w)
        to[w] = from[w];
}

// recursivly remove non-alpha chars
void clean(char* word) {
    int from = 0, to = 0;
    while(word[from])
        if(isalpha(word[from]))
            word[to++] = word[from++];
        else
            from++;
    word[to] = '\0';
}
