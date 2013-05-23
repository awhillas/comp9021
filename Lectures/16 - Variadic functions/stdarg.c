/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the use of the stdarg.h library,                   *
 *              and more specifically, the va_list type and the                *
 *              va_start, va_arg, va_end and va_copy functions.                *
 *              In a first example function, the number of                     *
 *              variable arguments is provided by a nonvariable argument.      *
 *              In a second example function, the number of                    *
 *              variable arguments is computed from a nonvariable argument.    *
 *              In a third example function, the number of                     *
 *              variable arguments is indicated by the last variable argument  *
 *              playing the role of a flag.                                    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

double max(int, ...);
char *operate_on_strings(char *, char *, ...);
int divisions(int, ...);

int main(void) {
    printf("Max of 4.1 and 1.2: %.1f\n", max(2, 4.1, 1.2));
    printf("Max of 4.1, 1.2 and 6.3: %.1f\n", max(3, 4.1, 1.2, 6.3));
    printf("Max of 4.1, 1.2, 6.3 and 2.4: %.1f\n", max(4, 4.1, 1.2, 6.3, 2.4));
    printf("Max of 4.1, 1.2, 6.3, 2.4, 8.5, 3.6 and 5.7: %.1f\n\n",
           max(7, 4.1, 1.2, 6.3, 2.4, 8.5, 3.6, 5.7));

    printf("Resulting string: %s\n\n",
           operate_on_strings("abcde", "12345",
                              "select", 1,
                              "ignore",
                              "select", 1,
                              "select", 2,
                              "ignore"));
    
    printf("Divisions determined by the sequence 2 and 3:\n");
    divisions(2, 3, 0);
    printf("Divisions determined by the sequence 2, 3 and 5:\n");
    divisions(2, 3, 5, 0);
    printf("Divisions determined by the sequence 2, 3, 5 and 7:\n");
    divisions(2, 3, 5, 7, 0);
    printf("Divisions determined by the sequence 2, 3, 2, 3 and 3:\n");
    divisions(2, 3, 2, 3, 3, 0);
    return EXIT_SUCCESS;
}

/* Computes the max of n numbers of type double. */
double max(int n, ...) {
    va_list ap;
    va_start(ap, n);
    double max = 0;
    for (int i = 0; i < n; ++i) {
        double x = va_arg(ap, double);
        max = x > max ? x : max;
    }
    va_end(ap);
    return max;
}

/* Takes 2 strings s1 and s2 of the same length l and a sequence of actions of length l,
 * the ith action, 1 <= i <= l, being either to ignore the ith elements of s1 and s2,
 * or to select the ith element of s1, or to select the ith element of s2,
 * and returns the resulting string.
 * The action to ignore an element is supposed to be indicated by one argument, namely,
 * the constant string "ignore", and the action to select an element from a string
 * is supposed to be indicated by two arguments, namely, the constant string "select" and
 * either 1 or 2 to refer to s1 or s2, respectively. */
char *operate_on_strings(char *s1, char *s2, ...) {
    int length = 0;
    while (*s1++)
        ++length;
    s1 -= length + 1;
    char *s = malloc((length + 1) * sizeof(char));
    va_list ap;
    va_start(ap, s2);
    int i = 0;
    while (length--) {
        char *action = va_arg(ap, char *);
        if (!strcmp(action, "ignore")) {
            ++s1;
            ++s2;
        }
        else if (va_arg(ap, int) == 1) {
            s[i++] = *s1++;
            ++s2;
        }
        else {
            s[i++] = *s2++;
            ++s1;
        }
    }
    s[i] = '\0';
    va_end(ap);
    return s;
}

/* The function is expected to take a sequence of ints of the form
 * (d_1, ..., d_k, 0) such that k >= 2, d_1 != 0, ..., d_k != 0, and computes
 * n_1 = 1000000 / d_1, n_2 = n_1 / d_2, ..., n_k = n_{k-1} / d_k
 * and if k > 2 and n_k is odd, n_{k+1} = n_k / d_3
 * and if k > 3 and n_{k+1} is odd, n_{k+2} = n_{k+1} / d_4, ...,
 * until either an even number is obtained or 2k-2 numbers have been generated,
 * and prints out n_1, n_2, ..., n_k and on the next line n_{k+1}, n_{k+2} ...
 * The last variable argument, equal to 0, plays the role of a flag. */
int divisions(int d, ...) {
    va_list ap, ap_except_first;
    va_start(ap, d);
    /* We assume that the nonvariable argument is not equal to 0. */
    int n = 1000000 / d;
    printf("%7d", n);
    /* We assume that the first variable argument exists and is not equal to 0. */
    n /= va_arg(ap, int);
    printf("%7d", n);
    /* First variable argument has been processed, and ap is now pointing
     * to remaining arguments, as ap_except_first will. */
    va_copy(ap_except_first, ap);
    while (d = va_arg(ap, int)) {
        n /= d;
        printf("%7d", n);
    }
    printf("\n              ");
    while (n % 2 && (d = va_arg(ap_except_first, int))) {
        n /= d;
        printf("%7d", n);
    }
    putchar('\n');
    va_end(ap);
    va_end(ap_except_first);
    return n;
}

    
    
    
    
    
        
                    
            
        
            
     
    

