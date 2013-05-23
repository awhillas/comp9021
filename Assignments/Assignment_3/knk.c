/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: A program that will solve Knights and Knaves problems.         *
 *                                                                             *
 * Written by: Alexander Whillas for COMP9021                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Sir listing type.
#define AND_KNIGHTS 0
#define OR_KNIGHTS 1
#define AND_KNAVES 2
#define OR_KNAVES 3


typedef struct words {
    // Begining & ending words...
    int first;
    int last;
    // quoted range...
    int open;
    int close;
    // Semantics
    int speaker;    // Sir index.
    int type;       // Sir listing type. 
} Sentence;


/**
 * Is the given integer in the array (of int.s)?
 */
bool in_array(int i, int array[], int size) {
    for(int j = 0; j < size; ++j)
        if(array[j] == i)
            return true;
    return false;
}

void print_array(char * array[], int size) {
    for(int i = 0; i < size; i++)
        printf(" %s", array[i]);
}

/**
 * Count the number, n, of Sirs where n >= 2 recursivly.
 */
int count_sirs(int i, char * text[]) {
    int count = 1;
    if(strcmp(text[i], "and") != 0)
        count += count_sirs(++i, text);
    return count;
}

int find_speaker(char * text[], Sentence s) {
    for (int i = s.first; i <= s.last; i++)
        if (i < s.open || i > s.close)
            if (strcmp(text[i], "Sir") == 0)
                return i + 1;
    return -1;
}

int find_index(char * needle, char * haystack[], int size) {
    for (int i = 0; i < size; i++)
        if (strcmp(needle, haystack[i]) == 0)
            return i;
    return -1;
}



/**
 * Compare 2 strings. Cmparison funciton for qsort
 */
int cmpstr(const void * a, const void * b) {    
    return(strcmp( *(char * const *) a, *(char * const *) b ));
}

int main(int argc, char * argv[]) {

    if (argc == 1)
        return EXIT_SUCCESS;

    printf("Number of words: %d\n", argc - 1);

    // Clean the input a bit. and count sentences.
    
    int nb_of_sentences = 0;
    int nb_of_sir_occurances = 0;
    for (int i = 1; i < argc; i++) {
        int length = strlen(argv[i]);
        if(argv[i][length - 1] == '"' && ispunct(argv[i][length - 2])) {
            argv[i][length - 1] = argv[i][length - 2];
            argv[i][length - 2] = '"';
        }
        // Count sentences
        char last = argv[i][length - 1];
        if (last == '.' || last == '!' || last == '?')
            nb_of_sentences++; 
        // Count Sir occurances (double counts).
        if(strcmp(argv[i], "Sir") == 0)
            nb_of_sir_occurances++;
        if(strcmp(argv[i], "Sirs") == 0)
            nb_of_sir_occurances += count_sirs(i + 1, argv);
    }
    printf("Number of Sentences: %d\n", nb_of_sentences);
    printf("Number of occurences of Sirs: %d\n", nb_of_sir_occurances);
    
    // Sentences
    
    int end_of_sentences[nb_of_sentences];
    int current_sentence = 0;
    for (int i = 1; i < argc; i++) {
        int length = strlen(argv[i]);
        char last = argv[i][length - 1];
        if (last == '.' || last == '!' || last == '?')
            end_of_sentences[current_sentence++] = i; 
    }
    
    // Sirs
    
    int sir_occurances[nb_of_sir_occurances];
    int current_sir = 0;
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "Sir") == 0)
            sir_occurances[current_sir++] = i + 1;
        if(strcmp(argv[i], "Sirs") == 0) 
            while(true) {
                i++;
                if(strcmp(argv[i], "and") != 0)
                    sir_occurances[current_sir++] = i;
                else {
                    sir_occurances[current_sir++] = i + 1;
                    break;
                }
            }
    }
    // Trim off punctuation from end of Sir names:
    for (int i = 0; i < nb_of_sir_occurances; i++) {
        int word = sir_occurances[i];
        int length = strlen(argv[word]);
        if(ispunct(argv[word][length - 1]))
            argv[word][length - 1] = '\0';
    }
    // Count distince Sirs:
    // Too lazy to write this loop twice...
    char * sirs[nb_of_sir_occurances]; 
    // ...and if we know this we can ignore the excess spaces.
    int nb_of_sirs = 0; 
    for(int i = 0; i < nb_of_sir_occurances; i++) {
        int current_sir = sir_occurances[i];
        bool duplicate = false;
        // Check if the current Sir has occured previously...
        for(int j = 0; j < i; j++) {
            int previous_sir = sir_occurances[j];
            if(strcmp(argv[current_sir], argv[previous_sir]) == 0) {
                duplicate = true;
                break;
            }
        }
        if(!duplicate)
            sirs[nb_of_sirs++] = argv[current_sir];
    }
    // Sort the Sirs
    qsort(sirs, nb_of_sirs, sizeof(char *), cmpstr);

    // Find Sir Statments
    
    Sentence sentences[nb_of_sentences];   // Sentences data.
    int current_begin = 1;  // coz argv inclues the program name at 0
    for (int s = 0; s < nb_of_sentences; s++) {
        Sentence current_s = {current_begin, end_of_sentences[s], -1, -1, -1, -1};
        for (int w = current_begin; w <= end_of_sentences[s]; w++) {
            // Look for quotes...
            if(argv[w][0] == '"') {
                current_s.open = w++;
                do {
                    int length = strlen(argv[w]);
                    for (int c = 0; c < length; c++)
                        if(argv[w][c] == '"') {
                            current_s.close = w;
                            break;
                        }
                    if(current_s.close != -1)
                        break;
                } while (++w <= end_of_sentences[s]); 
            }
        }
        current_begin = end_of_sentences[s] + 1;
        sentences[s] = current_s;
    }
    // Look for Sir who is speaking.
    for (int s = 0; s < nb_of_sentences; s++)
        if (sentences[s].open != -1) {
            int speaker_i = find_speaker(argv, sentences[s]);
            if(speaker_i != -1)
                sentences[s].speaker = find_index(argv[speaker_i], sirs, nb_of_sirs);
        }
    // match phrase to one of the 8 templates.

    
    
    
    // Output testing.

    for (int i = 1; i < argc; i++){
        printf("%s ", argv[i]);
        if(in_array(i, end_of_sentences, nb_of_sentences))
            printf("\n");
    }
    printf("The Sirs are:");
    print_array(sirs, nb_of_sirs);
    printf("\n");
}
