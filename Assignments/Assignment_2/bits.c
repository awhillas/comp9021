#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int count_bits(unsigned int n) {
    unsigned int count = 0;
    while(n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
int bit_to_number(unsigned int n) {
    int i = 0;
    while(i++ < 9)
        if(n & 1 << i)
            return i;
    return 0;
}

int main(void) {

    unsigned int i = 0; 

    printf("count: %d\n", count_bits(i));
    printf("value: %d\n", bit_to_number(i));
    
    i |= 1 << 11;
    i |= 1 << 5;

    printf("count: %d\n", count_bits(i));
    printf("value: %d\n", bit_to_number(i));
   
    i |= 1 << 3;
    i |= 1 << 9;

    printf("\ncount: %d\n", count_bits(i));
    printf("value: %d\n", bit_to_number(i));

    bool a = false;
    a |= true;
    printf("a:%s\n", a ? "True": "False");

    a |= false;
    printf("a:%s\n", a ? "True": "False");
    
    a |= true;
    printf("a:%s\n", a ? "True": "False");

}


