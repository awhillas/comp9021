/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * Description: Finds a strictly positive number *
 * * that satisfies 13 out of the 15 conditions: *
 * * - It is a multiple of 2, 3, 4, 5, 6, 7, 8, 9 and 10. *
 * * - It is smaller than 1000, 750, 550 and 500. *
 * * - It is greater than 400 and 450. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
int main(void) {
  int wrong;
  /** 
   * Search number less than 750 (2 contraints) and multipules of 6 (hence
   * multipules of 2, 3 & 6.
   */
  for (int N = 6; N < 750; N += 6) {
   
      if (wrong == 2)
        printf("N = %d is a solution.\n", N);
  }
  return EXIT_SUCCESS;
}
