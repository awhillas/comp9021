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
#define KNIGHTS true
#define KNAVES false
#define CONJUNC 0
#define DISJUNC 1

// The 8 sentence types
#define S_AT_LEAST 0
#define S_AT_MOST 1
#define S_EXACTLY 2
#define S_ALL_OF_US 3
#define S_I_AM 4
#define S_SIR_IS_A 5
#define S_DISJUNC_IS_A 6
#define S_CONJUNC_IS_A 7


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
    // Object(s)
    int op;    // How the Sirs are collectivly grouped.
    int sirs_start; // where the Sirs conjunction/disjunction starts. 
    bool knights;
    unsigned sirs;  // boolean array indexed as sirs[] 1=knight,0=knave
} Sentence;


unsigned sir_find_sirs(char * [], int, char *, char * [], int, unsigned); 
int find_index(char *, char * [], int);

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

/**
 * Find the sirs in a conjunction/disjunction phrase, single Sir, "I" and "All".
 */
void find_sirs(char * text[], Sentence * s, char * sirs[], int nb_of_sirs) {
    if (s->sirs_start != -1) {
        char * looking_for = (s->op == DISJUNC) ? "or" : "and";
        s->sirs = sir_find_sirs(text, s->sirs_start + 1, looking_for, sirs, nb_of_sirs, 0);
    }
}
/**
 * Recurisvly build up a boolean array (unsigned int) with indexes matching those in the sirs[] array
 */ 
unsigned sir_find_sirs(char * text[], int current_i, char * delimiter, char * lookup[], int nb_of_sirs, unsigned output) {
    if (strcmp(text[current_i], delimiter) != 0) {
        int sir_i = find_index(text[current_i], lookup, nb_of_sirs);
        if (sir_i != -1) {
            output |= 1 << sir_i;
            return sir_find_sirs(text, current_i + 1, delimiter, lookup, nb_of_sirs, output);
        }
    }
    else {
        // At the end so grab the last Sir and return.
        int sir_i = find_index(text[current_i + 1], lookup, nb_of_sirs);
        if (sir_i != -1)
            output |= 1 << sir_i;
    }
    return output;
}

/**
 * Finds the name of the speaker
 */ 
int find_speaker(char * text[], Sentence s) {
    for (int i = s.first; i <= s.last; i++)
        if (i < s.open || i > s.close)
            if (strcmp(text[i], "Sir") == 0)
                return i + 1;
    return -1;
}

/**
 * finds the index of the given string in the the given array of strings
 */
int find_index(char * needle, char * haystack[], int size) {
    for (int i = 0; i < size; i++)
        if (strcmp(needle, haystack[i]) == 0)
            return i;
    return -1;
}

/**
 * Match the sentence to one of the 8 phrase templates and fill in the missing
 * info in the Sentence struct passed.
 */
void match_phrase(Sentence * s, char * text[]) {
    text[s->open][1] = tolower(text[s->open][1]);
    // Are we talking about Knights or Knaves
    s->knights = (strcmp(text[s->close], "Knight\"") == 0) ? true: false;
    // Match sentence type...
    if (strcmp(text[s->open], "\"at") == 0 ) {
        if (strcmp(text[s->open + 1], "least") == 0) {
            s->type = S_AT_LEAST;
            s->op = CONJUNC;
            s->sirs_start = s->open + 4;
        }
        else if (strcmp(text[s->open + 1], "most") == 0) {
            s->type = S_AT_MOST;
            s->op = CONJUNC;
            s->sirs_start = s->open + 4;
        }
    } 
    else if (strcmp(text[s->open], "\"exactly") == 0) {
        s->type = S_EXACTLY;
        s->op = CONJUNC;
        s->sirs_start = s->open + 3;
    }
    else if (strcmp(text[s->open], "\"all") == 0) {
        s->type = S_ALL_OF_US;
        s->op = CONJUNC;
        s->sirs_start = s->open;
    }
    else if (strcmp(text[s->open], "\"i") == 0) {
        s->type = S_I_AM;    // This is ether a contradiction or a truisum...
        s->op = -1;          // ... so we don't care what op it is.
        s->sirs_start = s->open;
    }
    else if (strcmp(text[s->open], "\"sir") == 0 && strcmp(text[s->open + 2], "is")) {
        s->type = S_SIR_IS_A;
        s->op = CONJUNC;
        s->sirs_start = s->open + 1;
    }
    // Tricky ones, match from the end.
    else if (strcmp(text[s->close - 2], "is") == 0 && strcmp(text[s->close - 1], "a") == 0) {
        s->type = S_DISJUNC_IS_A;
        s->op = DISJUNC;
        s->sirs_start = s->open;
    }
    else if (strcmp(text[s->close - 2], "are") == 0) {
        s->type = S_CONJUNC_IS_A;
        s->op = CONJUNC;
        s->sirs_start = S->open;
    }
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
        Sentence current_s = {current_begin, end_of_sentences[s], -1, -1, -1, -1, -1, -1, -1, 0};
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
                    if(current_s.close != -1) {
                        // Remove punctuation and move on...
                        if(ispunct(argv[w][length - 1]))
                            argv[w][length - 1] = '\0';
                        break;
                    }
                } while (++w <= end_of_sentences[s]); 
            }
        }
        current_begin = end_of_sentences[s] + 1;
        sentences[s] = current_s;
    }
    // Look for Sir who is speaking.
    for (int i = 0; i < nb_of_sentences; i++) {
        Sentence * s = &sentences[i];
        if (s->open != -1) {
            int speaker_i = find_speaker(argv, *s);
            if(speaker_i != -1)
                s->speaker = find_index(argv[speaker_i], sirs, nb_of_sirs);
            // match phrase to one of the 8 templates.
            match_phrase(s, argv);
            find_sirs(argv, s, sirs, nb_of_sirs);
        }
    }
    
    
    
    
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
