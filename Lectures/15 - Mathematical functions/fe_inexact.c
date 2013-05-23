/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the difference between nearbyint() and rint().     *
 *              Also illustates the FE_INEXACT exception flag and the          *
 *              fegetexceptflag() and feclearexcept() functions defined in     *
 *              fenv.h.                                                        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>

int main(void) {
    printf("FE_INEXACT: %d\n", FE_INEXACT);
    fexcept_t flag;
    double x = rint(1);
    fegetexceptflag(&flag, FE_INEXACT);
    printf("After executing x = rint(1): %d\n", flag);
    x = rint(1.5);
    fegetexceptflag(&flag, FE_INEXACT);
    printf("After executing x = rint(1.5): %d\n", flag);
    x = rint(1);
    fegetexceptflag(&flag, FE_INEXACT);
    printf("After executing x = rint(1): %d\n", flag);
    feclearexcept(FE_INEXACT);
    x = rint(1);
    fegetexceptflag(&flag, FE_INEXACT);
    printf("After executing x = rint(1): %d\n", flag);
    x = nearbyint(1.5);
    fegetexceptflag(&flag, FE_INEXACT);
    printf("After executing x = nearbyint(1.5): %d\n", flag);
    return EXIT_SUCCESS;
}

