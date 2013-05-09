/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Purpose: 
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

void show(void (*)(char *), char *);
char string[] = "comp9021";
void to_upper(char *);



int main(void) {
    show(to_upper, string);
    return EXIT_SUCCESS;
}

void to_upper(char *str) {
    char c;
    while ((c = *str) != '\0') {
        if (c >= 'a' && c <= 'z')
            *str = c + 'A' - 'a';
        ++str;
    }
}

void show(void (*pt)(char *), char *str) {
    (*pt)(str);
    while (*str != '\0')
        putchar(*str++);
    putchar('\n');
}


        
