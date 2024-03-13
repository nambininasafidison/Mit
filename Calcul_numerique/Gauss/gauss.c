#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void triangularisation(float **first, float *second, int dim) {
    for(int k = 0; k < dim; k++) {
        // float piv = fabs(first[k][k]);
        // int lpiv = k;
        // for(int i = k+1; i<dim;i++){
        //     if(fabs(first[k][i]) > piv){
        //         piv = fabs(first[k][i]);
        //         lpiv = k;
        //     }
        // }

        // if(lpiv!=k){
        //     float* tmp = first[lpiv];
        //     first[lpiv] = first[k];
        //     first[k] = tmp;
        // }

        for(int i = k+1; i < dim; i++) {
            for(int j = k+1; j < dim; j++) {
                first[i][j] = first[i][j]-((first[i][k] / first[k][k])*first[k][j]);
            }
            second[i] = second[i]-((first[i][k]/first[k][k])*second[k]);
            first[i][k] = 0;
        }
    }
}

float *resolution(float **first, float *second, int dim) {
    float tmp = 0;
    float *ans = (float*)malloc(sizeof(float)*dim);
    triangularisation(first, second, dim);
    for(int i = dim-1; i >= 0; i--) {
        tmp = 0;
        for(int j = 1+i; j <= dim; j++) {
            tmp += first[i][j]*ans[j];
        }
        ans[i] = (1/first[i][i])*(second[i]-tmp);
    }
    return ans;
}

void print(float **matrix, int dim) {
    printf("\n");
    for(int i = 0; i < dim ; i++) {
        for(int j = 0; j < dim; j++) {
            printf("%g\t", matrix[i][j]);
        }
        printf("\n");
    } 
}

void p(float *f) {
    printf("\n");
    for(int i =0; i < 3; i++) {
        printf("%g\t", f[i]);
    }
    printf("\n");
}