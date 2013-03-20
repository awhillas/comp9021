/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by **** for COMP9021                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_SETS 3

/* ...returns the number of digits found */
void display_set_coded_by(int);
/* Returns the maximum distance between two integers modulo 10 coded in set,
 * unless that distance is less than threshold, in which case threshold
 * is the returned value. */
int max_distance_at_least_equal_to_in(int threshold, int set);

int main(void) {
    int n1, n2, n3;
    int n[NUMBER_OF_SETS];
    int distances[NUMBER_OF_SETS];
    printf("Enter a first number at most equal to 1023: ");
    scanf("%d", &n[0]);
    printf("Enter a second number at most equal to 1023: ");
    scanf("%d", &n[1]);
    printf("Enter a third number at most equal to 1023: ");
    scanf("%d", &n[2]);
    printf("The largest distance between two consecutive digits in one of the sets\n");
/*
    display_set_coded_by(n1);
    display_set_coded_by(n2);
    display_set_coded_by(n3);
*/
    for(int i = 0; i < NUMBER_OF_SETS; i++)
        display_set_code_by(n[i]);
    
    int max_distance = 0;

    /* ... REPLACE THIS COMMENT WITH YOUR CODE ... */
    for(int i = 0; i < NUMBER_OF_SETS; i++) {
        int distance = max_distance_at_least_equal_to_in(1, n[i]);
        if(distance > max_distance)
            max_distance = distance;
    }

    printf("(modulo 10, i.e., considering that 0 follows 9) is equal to %d.\n", max_distance); 
    return EXIT_SUCCESS;
}

void display_set_coded_by(int n) {
    printf("    {");
    bool digits_found = false;
    for (int i = 0; i < 10; ++i)
        if (n & 1 << i) {
            if (digits_found)
                printf(", %d", i);
            else
                printf("%d", i);
            digits_found = true;
        }
    printf("}\n");
}

int max_distance_at_least_equal_to_in(int threshold, int n) {
    /* ... REPLACE THIS COMMENT WITH YOUR CODE ... */
    int last_digit = -1;
    int distance = 0;
    for (int i = 0; i < 10; ++i)
        if (n & 1 << i) {
            if (last_digit > -1)
                printf(", %d", i);
            else
                distance = 10;
            last_digit = i;
        }
}

