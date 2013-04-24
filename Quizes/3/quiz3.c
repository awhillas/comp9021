/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description:                                                                * 
 *                                                                             *
 * Written by Alexander Whillas (z3446737) for COMP9021                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define NB_OF_BITS_FOR_NUMBER 32
#define NB_OF_BITS_FOR_EXPONENT 8
#define NB_OF_BITS_FOR_DECIMAL_PART 23

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void complain(void);

int main(void) {
    char sign;
    printf("Enter the sign of a normalised floating point number not equal to 0: ");
    scanf("%c", &sign);
    if (sign != '+' && sign != '-')
        complain();
    int exponent;
    printf("Enter the exponent: ");
    scanf("%d", &exponent);
    if (exponent <= -pow(2, NB_OF_BITS_FOR_EXPONENT - 1) + 1 ||
        exponent >= pow(2, NB_OF_BITS_FOR_EXPONENT - 1))
        complain();
    double mantissa;
    printf("Enter the decimal part: ");
    scanf("%lf", &mantissa);
    if (mantissa < 0 || mantissa >= 1)
        complain();
    int bits[NB_OF_BITS_FOR_NUMBER] = {0};
    
    
    
    /* ... REPLACE THIS COMMENT WITH YOUR CODE ... */
    if(sign == '-')
        bits[0] = 1;
    
    exponent += 127;
    for(int i = 0; i < 8; i++)
        if(exponent & 1 << i)
            bits[8-i] = 1;
    
    for(int i = 0; i < NB_OF_BITS_FOR_DECIMAL_PART; i++) {
        if(mantissa - 1 / pow(2, i) >= 0) {
            bits[i + 8] = 1;
            mantissa -= 1 / pow(2, i);
        }
    }
    
    printf("The %d bits of %c2^%d x %.7f, with bytes in their \"natural\" order, are:\n    ",
           NB_OF_BITS_FOR_NUMBER, sign, exponent, 1 + mantissa);
    for (int i = 0; i < NB_OF_BITS_FOR_NUMBER; ++i) {
        putchar(bits[i] + '0');
        if (i % 8 == 7)
            putchar(' ');
    }
    putchar('\n');
    return EXIT_SUCCESS;
}

void complain(void) {
    printf("You did not provide me with what I asked for!\n");
    exit(EXIT_FAILURE);
}
