/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: A program that will
 *              - take as command line arguments descriptions of types,
 *                possibly associated with variable names, some of those
 *                variable names possibly referring to other variable names,
 *              - check that those descriptions are correct according to some
 *                well defined set of rules, and
 *              - output appropriate C representations of those descriptions.
 
                 "S_" denotes a state.
                 "m_" denotes a mapping.
                 "w_" denotes a word.
 * 
 * Written by: Andrea Finno (apfi184) for COMP9021                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/* Define mapping struct used to pair states for state machine */
typedef struct mapping {
    char * word;
    int identifier;
} Mapping;

/* Define function pointer to using state structure */
typedef bool (*State_function)(int);

/* Main state structure. Stores an identifier, a mapping struct,
a function pointer and output text for basic types */
typedef struct state {
   int identifier;
   Mapping * transitions;
   State_function process_state;
   char * print_name;
} State;

/* Define max out output length per definition */
#define MAX_DEF_LENGTH 100

/* Define names for procedures */
#define S_START 0
#define S_END 1

/* Define names for basic types */
#define S_SIGNED 2
#define S_SIGNED_CHAR 3
#define S_SIGNED_INT 4
#define S_SIGNED_INT_SHORT 5
#define S_SIGNED_INT_LONG 6
#define S_SIGNED_INT_LONG_LONG 7
#define S_SIGNED_SHORT 8
#define S_SIGNED_LONG 9
#define S_SIGNED_LONG_LONG 10
#define S_UNSIGNED 11
#define S_UNSIGNED_CHAR 12
#define S_UNSIGNED_INT 13
#define S_UNSIGNED_INT_SHORT 14
#define S_UNSIGNED_INT_LONG 15
#define S_UNSIGNED_INT_LONG_LONG 16
#define S_UNSIGNED_SHORT 17
#define S_UNSIGNED_LONG 18
#define S_UNSIGNED_LONG_LONG 19
#define S_INT 20
#define S_INT_SHORT 21
#define S_INT_LONG 22
#define S_INT_LONG_LONG 23
#define S_LONG 24
#define S_LONG_LONG 25
#define S_DOUBLE 26
#define S_DOUBLE_LONG 27
#define S_CHAR 28
#define S_SHORT 29
#define S_FLOAT 30
#define S_VOID 31

/* Define names for complex types */
#define S_FUNCTION 32
#define S_FUNCTIONS 33
#define S_POINTER 34
#define S_POINTERS 35
#define S_ARRAY 36
#define S_ARRAYS 37

/* Define names for literals */
#define S_AN_UPPER 38
#define S_A_UPPER 39
#define S_AN_LOWER 40
#define S_A_LOWER 41
#define S_TYPE 42
#define S_DATUM 43
#define S_DATA 44

#define S_RETURNING_FROM_A_UPPER 45
#define S_RETURNING_FROM_A_LOWER 46
#define S_TO_FROM_A_UPPER 47
#define S_TO_FROM_A_LOWER 48

#define S_VARIABLE 49
#define S_COMPLEX_VARIABLE 50
#define S_RETURNING 51

bool process_input();
bool is_valid_transition(char *);
bool is_valid_variable(char *);
bool is_valid_number(char *);
bool is_valid_end(char *);

bool process_basic(int);
bool process_array(int);
bool process_pointer(int);
bool process_function(int);
bool process_datum(int);

State get_state_info(int);
void print_state_machine();
void print_current_state();
bool set_sentence_details();
bool process_sentence(int);
void add_to_output(char *);
bool append_to_definition(char *);
bool prepend_to_definition(char *);

/* Define reserved words */
char w_An[] = "An";
char w_A[]  = "A";
char w_an[] = "an";
char w_a[]  = "a";
char w_signed[]  = "signed";
char w_unsigned[]  = "unsigned";
char w_int[]  = "int";
char w_char[]  = "char";
char w_short[]  = "short";
char w_long[]  = "long";
char w_float[]  = "float";
char w_double[]  = "double";
char w_array[]  = "array";
char w_pointer[]  = "pointer";
char w_function[]  = "function";
char w_arrays[]  = "arrays";
char w_pointers[]  = "pointers";
char w_functions[]  = "functions";
char w_datum[]  = "datum";
char w_data[]  = "data";
char w_void[]  = "void";
char w_to[]  = "to";
char w_of[]  = "of";
char w_the[]  = "the";
char w_type[]  = "type";
char w_returning[]  = "returning";

char w_variable[]  = "?";
char w_end[]  = "!";

char *reserved_words[] = {
    w_An, w_A, w_an, w_a, w_signed, w_unsigned,
    w_int, w_char, w_short, w_long, w_float, w_double,
    w_array, w_pointer, w_function, w_arrays, w_pointers, w_functions,
    w_datum, w_data, w_void, w_to, w_of, w_the, w_type, w_returning,
    '\0'
};

/*
Define state mappings
All state are mapped to reserved words and are used to check what string paths can be followed.
*/
Mapping m_start[] = { {w_An, S_AN_UPPER}, {w_A, S_A_UPPER}, {NULL, 0} };
Mapping m_an_upper[] = { {w_int, S_INT}, {w_unsigned, S_UNSIGNED}, {w_array, S_ARRAY}, {NULL, 0} };
Mapping m_a_upper[] = { {w_char, S_CHAR}, {w_signed, S_SIGNED}, {w_short, S_SHORT}, {w_long, S_LONG}, {w_float, S_FLOAT}, {w_double, S_DOUBLE}, {w_pointer, S_POINTER}, {w_function, S_FUNCTION}, {NULL, 0} };

Mapping m_int[] = { {w_signed, S_SIGNED_INT}, {w_unsigned, S_UNSIGNED_INT}, {w_short, S_INT_SHORT}, {w_long, S_INT_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_int_short[] = { {w_signed, S_SIGNED_INT_SHORT}, {w_unsigned, S_UNSIGNED_INT_SHORT}, {w_end, S_END}, {NULL, 0} };
Mapping m_int_long[] = { {w_long, S_INT_LONG_LONG}, {w_signed, S_SIGNED_INT_LONG}, {w_unsigned, S_UNSIGNED_INT_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_int_long_long[] = { {w_signed, S_SIGNED_INT_LONG_LONG}, {w_unsigned, S_UNSIGNED_INT_LONG_LONG}, {w_end, S_END}, {NULL, 0} };

Mapping m_signed[] = { {w_char, S_SIGNED_CHAR}, {w_int, S_SIGNED_INT}, {w_long, S_SIGNED_LONG}, {w_short, S_SIGNED_SHORT}, {w_end, S_END}, {NULL, 0} };
Mapping m_signed_char[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_signed_int[] = { {w_long, S_SIGNED_INT_LONG}, {w_short, S_SIGNED_INT_SHORT}, {w_end, S_END}, {w_end, S_END}, {NULL, 0} };
Mapping m_signed_int_short[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_signed_int_long[] = { {w_long, S_SIGNED_INT_LONG_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_signed_int_long_long[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_signed_short[] = { {w_int, S_SIGNED_INT_SHORT}, {w_end, S_END}, {NULL, 0} };
Mapping m_signed_long[] = { {w_int, S_SIGNED_INT_LONG}, {w_long, S_SIGNED_LONG_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_signed_long_long[] = { {w_int, S_SIGNED_INT_LONG_LONG}, {w_end, S_END}, {NULL, 0} };

Mapping m_unsigned[] = { {w_char, S_UNSIGNED_CHAR}, {w_int, S_UNSIGNED_INT}, {w_long, S_UNSIGNED_LONG}, {w_short, S_UNSIGNED_SHORT}, {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_char[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_int[] = { {w_short, S_UNSIGNED_INT_SHORT}, {w_long, S_UNSIGNED_INT_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_int_short[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_int_long[] = { {w_long, S_UNSIGNED_INT_LONG_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_int_long_long[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_short[] = { {w_int, S_UNSIGNED_INT_SHORT}, {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_long[] = { {w_int, S_UNSIGNED_INT_LONG}, {w_long, S_UNSIGNED_LONG_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_unsigned_long_long[] = { {w_int, S_UNSIGNED_INT_LONG_LONG}, {w_end, S_END}, {NULL, 0} };

Mapping m_long[] = { {w_signed, S_SIGNED_LONG}, {w_unsigned, S_UNSIGNED_LONG}, {w_int, S_INT_LONG}, {w_long, S_LONG_LONG}, {w_double, S_DOUBLE_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_long_long[] = { {w_int, S_INT_LONG_LONG}, {w_signed, S_SIGNED_LONG_LONG}, {w_unsigned, S_UNSIGNED_LONG_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_double[] = { {w_long, S_DOUBLE_LONG}, {w_end, S_END}, {NULL, 0} };
Mapping m_double_long[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_char[] = { {w_signed, S_SIGNED_CHAR}, {w_unsigned, S_UNSIGNED_CHAR}, {w_end, S_END}, {NULL, 0} };
Mapping m_short[] = { {w_signed, S_SIGNED_SHORT}, {w_unsigned, S_UNSIGNED_SHORT}, {w_int, S_INT_SHORT}, {w_end, S_END}, {NULL, 0} };
Mapping m_float[] = { {w_end, S_END}, {NULL, 0} };
Mapping m_void[] = { {w_end, S_END}, {NULL, 0} };

Mapping m_array[] = { {w_datum, S_DATUM}, {w_data, S_DATA}, {w_pointer, S_POINTER}, {NULL, 0} };
Mapping m_pointer[] = { {w_void, S_VOID}, {w_datum, S_DATUM}, {w_pointer, S_POINTER}, {NULL, 0} };
Mapping m_function[] = { {w_void, S_VOID}, {w_datum, S_DATUM}, {w_pointer, S_POINTER}, {NULL, 0} };

Mapping m_datum[] = { {w_type, S_TYPE}, {NULL, 0} };
Mapping m_data[] = { {w_type, S_TYPE}, {NULL, 0} };
Mapping m_type[] = { {w_int, S_INT}, {w_unsigned, S_UNSIGNED}, {w_char, S_CHAR}, {w_signed, S_SIGNED}, {w_short, S_SHORT}, {w_long, S_LONG}, {w_float, S_FLOAT}, {w_double, S_DOUBLE}, {NULL, 0} };

Mapping m_end[] = { {NULL, 0} };

/*
Pair mappings to state machine, define functions to be executed on each state and the expect output for basic types
Usage: {STATE_CODE, STATE_MAPPING, STATE_FUNCTION, STATE_OUTPUT},
*/
State states[] = {
  {S_START, m_start, NULL, NULL},
  {S_AN_UPPER, m_an_upper, NULL, NULL},
  {S_A_UPPER, m_a_upper, NULL, NULL},
  
  {S_INT, m_int, &process_basic, "int"},
  {S_INT_SHORT, m_int_short, &process_basic, "short"},
  {S_INT_LONG, m_int_long, &process_basic, "long"},
  {S_INT_LONG_LONG, m_int_long_long, &process_basic, "long long"},
  
  {S_SIGNED, m_signed, &process_basic, "int"},
  {S_SIGNED_CHAR, m_signed_char, &process_basic, "signed char"},
  {S_SIGNED_INT, m_signed_int, &process_basic, "int"},
  {S_SIGNED_INT_SHORT, m_signed_int_short, &process_basic, "short"},
  {S_SIGNED_INT_LONG, m_signed_int_long, &process_basic, "long"},
  {S_SIGNED_INT_LONG_LONG, m_signed_int_long_long, &process_basic, "long long"},
  {S_SIGNED_SHORT, m_signed_short, &process_basic, "short"},
  {S_SIGNED_LONG, m_signed_long, &process_basic, "long"},
  {S_SIGNED_LONG_LONG, m_signed_long_long, &process_basic, "long long"},
  
  {S_UNSIGNED, m_unsigned, &process_basic, "unsigned"},
  {S_UNSIGNED_CHAR, m_unsigned_char, &process_basic, "unsigned char"},
  {S_UNSIGNED_INT, m_unsigned_int, &process_basic, "unsigned"},
  {S_UNSIGNED_INT_SHORT, m_unsigned_int_short, &process_basic, "unsigned short"},
  {S_UNSIGNED_INT_LONG, m_unsigned_int_long, &process_basic, "unsigned long"},
  {S_UNSIGNED_INT_LONG_LONG, m_unsigned_int_long_long, &process_basic, "unsigned long long"},
  {S_UNSIGNED_SHORT, m_unsigned_short, &process_basic, "unsigned short"},
  {S_UNSIGNED_LONG, m_unsigned_long, &process_basic, "unsigned long"},
  {S_UNSIGNED_LONG_LONG, m_unsigned_long_long, &process_basic, "unsigned long long"},
  
  {S_LONG, m_long, &process_basic, "long"},
  {S_LONG_LONG, m_long_long, &process_basic, "long long"},
  {S_DOUBLE, m_double, &process_basic, "double"},
  {S_DOUBLE_LONG, m_double_long, &process_basic, "long double"},
  {S_CHAR, m_char, &process_basic, "char"},
  {S_SHORT, m_short, &process_basic, "short"},
  {S_FLOAT, m_float, &process_basic, "float"},
  
  {S_VOID, m_void, NULL, "void"},
  
  {S_ARRAY, m_array, &process_array, NULL},
  {S_POINTER, m_pointer, &process_pointer, NULL},
  {S_FUNCTION, m_function, &process_function, NULL},
  
  {S_DATUM, m_datum, &process_datum, NULL},
  {S_DATA, m_data, &process_datum, NULL},
  {S_VOID, m_void, NULL, NULL},
  {S_TYPE, m_type, NULL, NULL},
  
  {S_END, m_end, NULL, NULL}
};

int current_state = S_START;
int current_position = 1;
char **words;
int word_count;
bool leading_type = true;
bool has_dot = false;
bool last_word = false;
int nb_of_sentences = 0;
int (*sentences)[2];
char **output_definitions = NULL;
char definition[MAX_DEF_LENGTH];
int nb_of_output_definitions = 0;
int nb_of_allocated_definitions = 0;

int main(int argc, char **argv) {
    
    words = argv;
    word_count = argc;
    
    if (argc == 1)
        return EXIT_SUCCESS;
    
    // Set details and run basic test on all sentences
    if (!set_sentence_details()) {
        printf("Incorrect input\n");
        return EXIT_FAILURE;
    }
    
    // Process all sentences
    for (int i = 0; i < nb_of_sentences; ++i) {
    
        // Clear definition output before processing sentence
        for (int j = 0; j < MAX_DEF_LENGTH; ++j)
            definition[j] = '\0';
        
        if (!process_sentence(i)) {
            printf("Incorrect input\n");
            return EXIT_FAILURE;
        }
        
        char * this_definition = malloc(MAX_DEF_LENGTH * sizeof(char));
        strcpy(this_definition, definition);
        
        // Add definition to final output
        add_to_output(this_definition);
    }
    
    // Print out all definitions
    for (int i = 0; i < nb_of_output_definitions; ++i)
        printf("%s\n", output_definitions[i]);
    
    return EXIT_SUCCESS;
}

bool process_sentence(int sentence_number) {

    /* Process each word in sentence */
    current_position = sentences[sentence_number][0]; // start
    State state_info;
    while (current_position <= sentences[sentence_number][1]) {
        
        state_info = get_state_info(current_state);
        
        if (state_info.process_state != NULL
            && !state_info.process_state(sentences[sentence_number][1]))
            return false;
        
        if (current_state != S_END 
            && !is_valid_transition(words[current_position]))
            return false;
        
        current_position++;
    }
    // Set position to end
    current_position = sentences[sentence_number][1];
    
    if (current_state != S_END && is_valid_end(words[current_position])) {
        state_info = get_state_info(current_state);
        if (!prepend_to_definition(" "))
            return false;
        if (!prepend_to_definition(state_info.print_name))
            return false;
        current_state = S_END;
    }
    
    if (current_state != S_END)
        return false;
    
    current_state = S_START;
    return true;
}

// Add to global output of definitions
void add_to_output(char * current_definition) {

    if (nb_of_output_definitions == nb_of_allocated_definitions) {
        if (nb_of_allocated_definitions == 0)
            nb_of_allocated_definitions = 2;
        else
            nb_of_allocated_definitions *= 2;
        
        void *_tmp = realloc(output_definitions, (nb_of_allocated_definitions * sizeof(char *)));
        
        output_definitions = (char **)_tmp;
    }
    
    output_definitions[nb_of_output_definitions] = current_definition;
    nb_of_output_definitions++;
    
}

// Prepend string to current definition
bool prepend_to_definition(char * syntax) {
    int new_length = strlen(syntax) + strlen(definition);
    if (new_length >= MAX_DEF_LENGTH)
        return false;
    memmove(definition+strlen(syntax), definition, strlen(definition));
    memcpy(definition, syntax, strlen(syntax));
    return true;
}

// Append string to current definition
bool append_to_definition(char * syntax) {
    int new_length = strlen(syntax) + strlen(definition);
    if (new_length >= MAX_DEF_LENGTH)
        return false;
    strcat(definition, syntax);
    return true;
}

/* Process basic data type */
bool process_basic(int sentence_end) {
    
    if (is_valid_variable(words[current_position])) {
        
        State state_info = get_state_info(current_state);
        
        if (!append_to_definition(state_info.print_name))
            return false;
        if (!append_to_definition(" "))
            return false;
        if (!append_to_definition(words[current_position]))
            return false;
        
        if (current_position == sentence_end)
            current_state = S_END;
        if ((current_position+1) < sentence_end)
            current_position++;
    }
    
    return true;
}

/* Process array definition */
bool process_array(int sentence_end) {

    if (is_valid_variable(words[current_position])) {
        
        // Start definition string
        if (!append_to_definition(words[current_position]))
            return false;
        
        if (current_position == sentence_end)
            return false;
        if (++current_position != sentence_end 
            && strcmp(words[current_position], w_of) != 0)
            return false;
        if (++current_position != sentence_end 
            && !is_valid_number(words[current_position]))
            return false;
            
        if (atoi(words[current_position]) > 1
            && strcmp(words[current_position+1], w_data) != 0)
            return false;
            
        if (atoi(words[current_position]) == 1
            && strcmp(words[current_position+1], w_datum) != 0)
            return false;
            
        // Insert array number
        if (!append_to_definition("["))
            return false;
        if (!append_to_definition(words[current_position]))
            return false;
        if (!append_to_definition("]"))
            return false;
        
        ++current_position;
        return true;
    }
    
    if (current_position == sentence_end)
        return false;
    if (current_position != sentence_end 
        && strcmp(words[current_position], w_of) != 0)
        return false;
    if (++current_position != sentence_end 
        && !is_valid_number(words[current_position]))
        return false;
        
    if (atoi(words[current_position]) > 1
        && strcmp(words[current_position+1], w_data) != 0)
        return false;
        
    if (atoi(words[current_position]) == 1
        && strcmp(words[current_position+1], w_datum) != 0)
        return false;
        
    // Insert array number
    if (!append_to_definition("["))
        return false;
    if (!append_to_definition(words[current_position]))
        return false;
    if (!append_to_definition("]"))
        return false;
    
    ++current_position;
    return true;
}

/* Process pointer definition */
bool process_pointer(int sentence_end) {

    if (is_valid_variable(words[current_position])) {

        if (!append_to_definition("*"))
            return false;
        if (!append_to_definition(words[current_position]))
            return false;
            
        if (current_position == sentence_end)
            return false;
        if (++current_position != sentence_end 
            && strcmp(words[current_position], w_to) != 0)
            return false;
        if (++current_position != sentence_end 
            && strcmp(words[current_position], w_a) == 0)
            ++current_position;
            
        return true;
    }
    
    if (current_position == sentence_end)
        return false;
    if (current_position != sentence_end 
        && strcmp(words[current_position], w_to) != 0)
        return false;
    if (!prepend_to_definition("*"))
        return false;
    if (++current_position != sentence_end 
        && strcmp(words[current_position], w_a) == 0)
        ++current_position;
        
    return true;
}

/* Process function definition */
bool process_function(int sentence_end) {
    
    if (is_valid_variable(words[current_position])) {
    
        if (!append_to_definition(words[current_position]))
            return false;
        if (!append_to_definition("()"))
            return false;
            
        if (current_position == sentence_end)
            return false;
        if (++current_position != sentence_end 
            && strcmp(words[current_position], w_returning) != 0)
            return false;
        if (++current_position != sentence_end 
            && strcmp(words[current_position], w_a) == 0)
            ++current_position;
        
        return true;
    }
    
    if (current_position == sentence_end)
        return false;
    if (current_position != sentence_end 
        && strcmp(words[current_position], w_returning) != 0)
        return false;
    if (!append_to_definition("()"))
        return false;
    if (++current_position != sentence_end 
        && strcmp(words[current_position], w_a) == 0)
        ++current_position;
        
    return true;
}

/* Process datum types */
bool process_datum(int sentence_end) {
    
    if (current_position == sentence_end)
        return false;
    if (current_position != sentence_end 
        && strcmp(words[current_position], w_of) != 0)
        return false;
    ++current_position;
    return true;
    
}

/* Check for a valid transition from one argument (i.e. word) to the next */
bool is_valid_transition(char *word) {
    
    State state_info = get_state_info(current_state);
    int j = -1;
    
    while(state_info.transitions[++j].word != NULL) {
        // Check for everything else
        if (strcmp(state_info.transitions[j].word, word) == 0) {
            current_state = state_info.transitions[j].identifier;
            return true;
        }
    }
    return false;
}

/* Check if a given variable is valid */
bool is_valid_variable(char *word) {
    
    // Check reserved words first (excluding normal reserved words by C)
    int i = -1;
    while(reserved_words[++i] != '\0') {
        if (strcmp(reserved_words[i], word) == 0)
            return false;
    }
    
    // Check for valid C variable construction
    i = -1;
    while(word[++i] != '\0') {
        if (i == 0 && (!isalpha(word[i]) && word[i] != '_'))
            return false;
        else if (!isalnum(word[i]) && word[i] != '_')
            return false;
    }
        
    return true;
}

/* Check if a given word can end the sentence */
bool is_valid_end(char *word) {
    State state_info = get_state_info(current_state);
    int j = -1;
    while(state_info.transitions[++j].word != NULL)
        if (state_info.transitions[j].identifier == S_END)
            return true;
    return false;
}

/* Check if a given number variable is valid */
bool is_valid_number(char *word) {
    int j = -1;
    while(word[++j] != '\0')
        if (!isdigit(word[j]))
            return false;
    return true;
}

State get_state_info(int state_identifier) {
    State state_info;
    int i = -1;
    while(states[++i].identifier != S_END)
        if (states[i].identifier == state_identifier)
            return states[i];
    return state_info;
}

/* Set start and end of sentences and remove dots */
bool set_sentence_details(void) {

    // Find number of sentences
    
    for (int i = 1; i < word_count; ++i)
        if (words[i][strlen(words[i])-1] == '.')
            nb_of_sentences++;
    
    /* Return false if invalid end of sentence */
    if (!nb_of_sentences || words[word_count-1][strlen(words[word_count-1])-1] != '.')
        return false;
    
    // Set sentence details
    sentences = malloc((nb_of_sentences*2)*sizeof(int));
    int sentence_number = 0;
    sentences[sentence_number][0] = 1;
    
    /* Mark start and end of sentences */
    for (int i = 1; i < word_count; ++i) {
        if (words[i][strlen(words[i])-1] == '.' && i != word_count-1) {
            sentences[sentence_number][1] = i;
            if (sentence_number < nb_of_sentences)
                sentences[sentence_number+1][0] = i+1; 
            sentence_number++;
        }
        /* Remove dots when found */
        if (words[i][strlen(words[i])-1] == '.')
            words[i][strlen(words[i])-1] = '\0';
    }
    sentences[sentence_number][1] = word_count-1;
    
    return true;
}
