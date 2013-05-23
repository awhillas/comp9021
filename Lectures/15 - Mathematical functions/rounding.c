/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates rounding as determined by rounding direction.      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>

int main(void) {
    printf("FE_DOWNWARD: %d\n", FE_DOWNWARD);
    printf("FE_UPWARD: %d\n", FE_UPWARD);
    printf("FE_TONEAREST: %d\n", FE_TONEAREST);
    printf("FE_TOWARDZERO: %d\n", FE_TOWARDZERO);
    printf("Current rounding direction: %d\n", fegetround());
    fesetround(FE_DOWNWARD);
    printf("Current rounding direction: %d\n", fegetround());
    printf("Rounding -1.5, -0.5, 0.5, 1.5 downward: %lf %lf %lf %lf\n",
           nearbyint(-1.5), nearbyint(-0.5), nearbyint(0.5), nearbyint(1.5));
    fesetround(FE_UPWARD);
    printf("Current rounding direction: %d\n", fegetround());
    printf("Rounding -1.5, -0.5, 0.5, 1.5 upward: %lf %lf %lf %lf\n",
           nearbyint(-1.5), nearbyint(-0.5), nearbyint(0.5), nearbyint(1.5));
    fesetround(FE_TONEAREST);
    printf("Current rounding direction: %d\n", fegetround());
    printf("Rounding -2.5, -1.5, -0.5, 0.5, 1.5, 2.5 to nearest: %lf %lf %lf %lf %lf %lf\n",
           nearbyint(-2.5), nearbyint(-1.5), nearbyint(-0.5), nearbyint(0.5), nearbyint(1.5), nearbyint(2.5));
    fesetround(FE_TOWARDZERO);
    printf("Current rounding direction: %d\n", fegetround());
    printf("Rounding -1.5, -0.5, 0.5, 1.5 toward 0: %lf %lf %lf %lf\n",
           nearbyint(-1.5), nearbyint(-0.5), nearbyint(0.5), nearbyint(1.5));
    return EXIT_SUCCESS;
}

