/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for characters and outputs for each digit     *
 *              how many occurrences of that digit have been input, if any.    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int count[10] = {0};
    printf("Enter characters: ");
    int c;
    while ((c = getchar()) != '\n')
        for (int i = '0'; i <= '9'; ++i)
            if (c == i) {
                ++count[i - '0'];
                break;
            }
    printf("Digits: ");
    for (int i = 0; i < 10; ++i)
        if (count[i])
            printf("%4d", i);
    putchar('\n');
    printf("Count:  ");
    for (int i = 0; i < 10; ++i)
        if (count[i])
            printf("%4d", count[i]);
    putchar('\n');
    return EXIT_SUCCESS;
}

          
