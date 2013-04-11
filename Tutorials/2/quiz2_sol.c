/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void display_set_coded_by(int);
/* Returns the maximum distance between two integers modulo 10 coded in set,
 * unless that distance is less than threshold, in which case threshold
 * is the returned value. */
int max_distance_at_least_equal_to_in(int threshold, int set);

int main(void) {
    int n1, n2, n3;
    printf("Enter a first number at most equal to 1023: ");
    scanf("%d", &n1);
    printf("Enter a second number at most equal to 1023: ");
    scanf("%d", &n2);
    printf("Enter a third number at most equal to 1023: ");
    scanf("%d", &n3);
    printf("The largest distance between two consecutive digits in one of the sets\n");
    display_set_coded_by(n1);
    display_set_coded_by(n2);
    display_set_coded_by(n3);
    int max_distance = 0;
    max_distance = max_distance_at_least_equal_to_in(max_distance, n1);
    max_distance = max_distance_at_least_equal_to_in(max_distance, n2);
    max_distance = max_distance_at_least_equal_to_in(max_distance, n3);
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

int max_distance_at_least_equal_to_in(int threshold, int set) {
    int first_nb_in_set = 0;
    while ((set & 1 << first_nb_in_set) == 0)
        if (++first_nb_in_set == 10)
            return threshold;
    int distance = 1;
    for (int i = 1; i <= 10; ++i)
        if ((set & 1 << (first_nb_in_set + i) % 10) == 0)
            ++distance;
        else {
            if (distance > threshold)
                threshold = distance;
            distance = 1;
        }
    return threshold;
}       
