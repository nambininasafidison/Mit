#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void display_result(float **a, float *x, int dim);
void get_dataf(int *dim, float ***a, float **b, float **x, float **y);
void cholesky(float **a, float *b, float *x, float *y, int dim);
void cleanup(float **ptr0, float *ptr, int dim);


int main() {
	printf("Resolution de A.x = B par la methode de Cholesky:\n");
// Data
	int dim = 3;
	float **a = NULL;
	float *b = NULL;
	float *x = NULL;
	float *y = NULL;
	int *p = NULL;
	get_dataf(&dim, &a, &b, &x, &y);
	
///Calcul
	cholesky(a, b, x, y, dim);

// result
	display_result(NULL, x, dim);

	return 0;
}

void get_dataf(int *dim, float ***a, float **b, float **x, float **y) {
	float *s = NULL, *z = NULL, *u = NULL;
	FILE *pf = fopen("data", "r");
	if(pf == NULL) {
		perror("FILE NOT FOUND !!!");
		exit(404);
	}
	fscanf(pf, "%d", dim);
	
	printf("%d\n", *dim);
	s = (float*)malloc(sizeof(float*)**dim);
	z = (float*)malloc(sizeof(float*)**dim);
	u = (float*)malloc(sizeof(float*)**dim);
	float **n = (float**)malloc(*dim*sizeof(float*));
	if(n == NULL) exit(1);
	for(int i = 0; i < *dim; i++) {
		n[i] = (float*)malloc(sizeof(float)**dim);
		if(n[i] == NULL) {
			cleanup(n, NULL, i);
			perror("ALLOCATION FAILED");
			exit(1);
		}
	}
	for(int i = 0; i < *dim; i++) {
		for(int j = 0; j<*dim; j++) {
			fscanf(pf, "%f", &n[i][j]);
		}
	}
	for(int i = 0; i< *dim; i++) {
		fscanf(pf, "%f", &s[i]);
	}
	
	*a = n;
	*b = s;
	*x = z;
    *y = u;
	// display_result(*a, *b, *dim);
}

void cholesky(float **a, float *b, float *x, float *y, int dim) {
	printf("Methode de Cholesky effectuee\n");
///Factorisation A = B.Bt
	float sum = 0;
    for(int i = 0 ; i < dim ; i++){
        for(int j = 0 ; j < i ; j++){
			sum = 0;
			for(int k = 0 ; k < j  ; k++){
				sum += a[i][k] * a[j][k];
				// printf("a[%d][%d] * a[%d][%d] = %f\n", i, k, j, k, sum);
			}
			a[i][j] = ( 1 / a[j][j]) * ( a[i][j] - sum ) ;
			// printf("(a[%d][%d] - %f) / a[%d][%d] = a[%d][%d]\n", i, j, sum, j, j, i, j);
        }
		sum = 0;
		for(int k = 0 ; k < i ; k++){
			sum += a[i][k] * a[i][k];
			// printf("a[%d][%d] * a[%d][%d] = %f\n", i, k, i, k, sum);
		}
		a[i][i] = sqrt( a[i][i] - sum );
		// printf("(sqrt(a[%d][%d] - %f) = a[%d][%d]\n", i, i, sum, i, i);
		// printf("ligne %d", i+1);
        display_result(a, NULL, dim);
    }

///Resolution de B.y = b
    float tmp = 0;
    for(int i = 0; i < dim; i++) {
		float tmp = 0;
        for(int j = 0; j < i; j++) {
            tmp += a[i][j]*y[j];
        }
        y[i] = (1/a[i][i])*(b[i]-tmp);
    }
	display_result(NULL, y, dim);

///Resolution de Bt.x = y

	for(int i = dim-1; i >= 0; i--) {
        float tmp = 0;
        for(int j = 1+i; j < dim; j++) {
            tmp += a[j][i]*x[j];
        }
        x[i] = (1/a[i][i])*(y[i]-tmp);
    }
}

void cleanup(float **ptr0, float *ptr, int dim) {
	if( ptr != NULL) {
		free(ptr);
	}
	if(ptr0 != NULL) {
		for(int i = 0; i<dim; i++) {
			free(ptr0[i]);
		}
		free(ptr0);
	}
}
void get_data(int *dim, float ***a, float **b, float **x) {
	float *v =  NULL;
	*dim = 4;
	v = (float*)malloc(sizeof(float)**dim);
	if(v == NULL) {
		exit(1);
		cleanup(NULL, v, 0);
	}
	for(int i = 0; i < *dim; i++) v[i] = i;
	*x = v;
	*b = malloc(sizeof(float)**dim);
	// for(int i = 0; i < *dim; i++) *b[i] = i*(i-0.12);
	float **y = (float**)malloc(*dim*sizeof(float*));
	if(y == NULL) exit(1);
	for(int i = 0; i < *dim; i++) {
		y[i] = (float*)malloc(sizeof(float)**dim);
		if(y[i] == NULL) {
			cleanup(y, NULL, i);
			exit(1);
		}
	}
	*a = y;
	printf("Voici les donnees\n");
}

void display_result(float **a, float *x, int dim) {
	printf("\nVoici le vecteur x\n");
	if(x != NULL) {

		for(int i = 0; i<dim; i++) {
			printf("%f\t", x[i]);
		}
	} 
	
	printf("\n");
	if(a != NULL) {
		for(int i = 0; i<dim; i++){
			for(int ii = 0; ii < dim; ii++){
				printf("%f\t",a[i][ii]);
			}
			printf("\n");
		}
	}
}
