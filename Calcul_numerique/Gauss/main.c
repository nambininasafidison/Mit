#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"


int main() {
    float b[3] = {4., 5., 11.};
    float **a = (float**)malloc(sizeof(float*)*3);
    for(int i = 0; i < 3; i++) {
        *(a+i) = (float*)malloc(sizeof(float)*3);
    }
    a[0][0] = 4; a[0][1] = 8; a[0][2] = 12;
    a[1][0] = 3; a[1][1] = 8; a[1][2] = 13;
    a[2][0] = 2; a[2][1] = 9; a[2][2] = 18;
    float *x = resolution(a, b, 3);
    print(a, 3);
    p(x);
    p(b);
    return 0;
}