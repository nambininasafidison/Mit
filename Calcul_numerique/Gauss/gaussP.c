#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void display_result(float **a, float *x, int dim);
void get_dataf(int *dim, float ***a, float **b, float **x, int **p);
void gauss(float **a, float *b, float **x, int dim, int *p);
void cleanup(float **ptr0, float *ptr, int dim);
void triangularisation(float **a, float *b, int dim, int *p);


int main() {
	printf("Resolution de A.x = B par la methode de Gauss:\n");
// Data
	int dim = 3;
	float **a = NULL;
	float *b = NULL;
	float *x = NULL;
	int *p = NULL;
	get_dataf(&dim, &a, &b, &x, &p);
	//display_result(a, NULL, dim);
	// triangularisation(a, b, dim, p);
	// for(int i = 0; i < dim; i++) {
	// 	printf("%d\t", p[i]);
	// }
// Calcul: methode de Gauss
	gauss(a, b, &x, dim, p);

// result
	display_result(NULL, x, dim);

	return 0;
}

void get_dataf(int *dim, float ***a, float **b, float **x, int **p) {
	int *v =  NULL;
	float *s = NULL, *z = NULL;
	FILE *pf = fopen("data0.txt", "r");
	if(pf == NULL) {
		perror("FILE NOT FOUND !!!");
		exit(404);
	}
	fscanf(pf, "%d", dim);
	
	printf("%d\n", *dim);
	v = (int*)malloc(sizeof(int)**dim);
	s = (float*)malloc(sizeof(float*)**dim);
	z = (float*)malloc(sizeof(float*)**dim);
	if(v == NULL) {
		cleanup(NULL, s, 0);
		exit(1);
	}
	for(int i = 0; i < *dim; i++) v[i] = i;
	// for(int i = 0; i < *dim; i++) *b[i] = i*(i-0.12);
	float **y = (float**)malloc(*dim*sizeof(float*));
	if(y == NULL) exit(1);
	for(int i = 0; i < *dim; i++) {
		y[i] = (float*)malloc(sizeof(float)**dim);
		if(y[i] == NULL) {
			cleanup(y, NULL, i);
			perror("ALLOCATION FAILED");
			exit(1);
		}
	}
	for(int i = 0; i < *dim; i++) {
		for(int j = 0; j<*dim; j++) {
			fscanf(pf, "%f", &y[i][j]);
		}
	}
	for(int i = 0; i< *dim; i++) {
		fscanf(pf, "%f", &s[i]);
	}
	
	*a = y;
	*b = s;
	*p = v;
	*x = z;
}
void triangularisation(float **a, float *b, int dim, int *p) { 
	int lpiv = 0, tmp = 0;
	float max = 0;
	for(int k = 0; k < dim; k++) {
		for(int i = k; i < dim; i++) {
			if(max<fabsf(a[p[i]][k])) {
				max = fabsf(a[p[i]][k]);
				lpiv = i;
			}
		}
	
		if(tmp!=k){
			tmp = p[k];
			p[k] = p[lpiv];
			p[lpiv] = tmp;
		}
		// printf("voici lpiv %d\t\n", lpiv);
		for(int i = 0; i < 3; i++) {
		}
		for(int i = k+1; i < dim; i++) {
			for(int j = k+1; j < dim; j++) {
				a[p[i]][j] = a[p[i]][j]-((a[p[i]][k] *a[p[k]][j]) / a[p[k]][k]);
			}
			b[p[i]] = b[p[i]]-((a[p[i]][k] * b[p[k]]) / a[p[k]][k]);
			a[p[i]][k] = 0;
		}
		
	}
	
	
}
float *resolution(float **a, float *b, int dim, int *p) {
    float tmp = 0;
    float *ans = (float*)malloc(sizeof(float)*dim);
    for(int i = dim-1; i >= 0; i--) {
		tmp = 0;
        for(int j = 1+i; j < dim; j++) {
            tmp += a[p[i]][j]*ans[j];
        }
        ans[i] = (1/a[p[i]][i])*(b[p[i]]-tmp);
    }
    return ans;
}

void gauss(float **a, float *b, float **x, int dim, int *p) {
	printf("Methode de Gauss effectuee\n");
    	triangularisation(a, b, dim, p);
    	*x = resolution(a, b, dim, p); 
}

// void gauss(float **a, float *b, float *x, int dim) {
// 	printf("Methode de Gauss effectuee\n");
// }
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
