
/* Define struct element for state machine */
typedef struct mapping {
    char * word;
    int identifier;
} Mapping;

typedef bool (*State_function)(int);

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
#define S_VOID 36

/* Define names for complex types */
#define S_FUNCTION 31
#define S_FUNCTIONS 50
#define S_POINTER 32
#define S_POINTERS 33
#define S_ARRAY 34
#define S_ARRAYS 35

/* Define names for literals */
#define S_AN_UPPER 37
#define S_A_UPPER 38
#define S_AN_LOWER 39
#define S_A_LOWER 40
#define S_TYPE 41
#define S_DATUM 42
#define S_DATA 43

#define S_RETURNING_FROM_A_UPPER 44
#define S_RETURNING_FROM_A_LOWER 45
#define S_TO_FROM_A_UPPER 46
#define S_TO_FROM_A_LOWER 47

#define S_VARIABLE 51
#define S_COMPLEX_VARIABLE 56
#define S_RETURNING 57