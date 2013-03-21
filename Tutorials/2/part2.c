/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *                                                                             *
 * By Alexander Whillas (z3446737) for COMP9021.                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define MAX 999
#define MIN 100

int main(void) {
    int size = MAX - MIN + 1;
    int numbers[size];
    for(int i = 0; i < size; i++)
        numbers[i] = 0;
    // 32^2 = 961

    for (int i = 31; i >= 0; i--)
        for (int j = 0; j < 32; j++) {
            int a =  i * i;
            int b = j * j;
            int sum = a + b;
            if (sum > MAX) break;
            if(sum < MAX && sum > MIN)
                numbers[sum - MIN] = 1;
        }
    
    for(int i = 0; i < size - 2; ++i)
        if(numbers[i] == 1 && numbers[i+1] == 1 && numbers[i+2] == 1) {
            printf("A solution is: %d, %d & %d \n", i+MIN, i+1+MIN, i+2+MIN);
            i += 2;
        }
}

                
