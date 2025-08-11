#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-6

void get_dataf(int *n, float **x, float **y, float *xmin, float *xmax, float *ymin, float *ymax, float *alpha, float **vect, float **U);
void gplotf(float xmin, float xmax, float ymin, float ymax, float *vect, int n);
void linLastSq(float *x, float *y, int dim, float *vect);
void leastSquare(float *x, float *y, int dim, float *vect);
float D0(int n, float *x, float *y, float a, float b);
float D1(int n, float *x, float *y, float a, float b);
void adust(float *x, float *y, float *vect, float *U, int n, float alpha);
void gradient(int n, float alpha, float *x, float *y, float *vect, float *U);


int main(){
    printf("Trace de courbes avec gnuplot\n");

/// Data intilisation
    int n = 0;
    float *vect = NULL, *U = NULL, xmin = 0, xmax = 0, ymin = -1.5, ymax = 50, alpha = 0, *x = NULL, *y = NULL;

/// Get data
    get_dataf(&n,  &x, &y, &xmin, &xmax, &ymin, &ymax, &alpha, &vect, &U);

/// Linear adjustement
    adust(x, y, vect, U, n, alpha);

/// Display with gnuplot
    gplotf(xmin, xmax, ymin, ymax, vect, n);


/// Cleanup


    return 0;
}

float D0(int n, float *x, float *y, float a, float b){
	float d0 = 0;
	for(int i=0 ; i<n ; i++){
		d0 += y[i] - (a + b * x[i]);
	}
    d0 *= (-2);
    return d0;
}

float D1(int n, float *x, float *y, float a, float b){
	float d1 = 0;
	for(int i=0 ; i<n ; i++){
		d1 += ( y[i] - (a + b * x[i]) ) * x[i];
	}
    d1 *= (-2);
    return d1;
}

void gradient(int n, float alpha, float *x, float *y, float *vect, float *U){
    float a = U[0], b = U[1];
    float 
		an1 = a - (alpha * D0(n, x, y, a, b)),
        bn1 = b - (alpha * D1(n, x, y, a, b));
    int i = 0;
    while(fabs( a - an1 ) + fabs( b - bn1 ) > 1e-6){
        i++;
        a = an1;
        b= bn1;
        an1 = a - (alpha * D0(n, x, y, a, b));
        bn1 = b - (alpha * D1(n, x, y, a, b));
    }
    vect[0] = b;
    vect[1] = a;
}

void linLastSq(float *x, float *y, int dim, float *vect){
    float xm = 0,
          ym = 0,
          s = 0,
          cov = 0,
          var = 0;
    for(int i=0; i<dim; i++)
        s += x[i];
    xm = s/dim;
    s = 0;
    for(int i=0; i<dim; i++)
        s += y[i];
    ym = s/dim;
    s = 0;
    for(int i=0; i<dim; i++)
        cov += (x[i] - xm) * (y[i] - ym);
    for(int i=0; i<dim; i++)
        var += (x[i] - xm) * (x[i] - xm);
    vect[0] = cov / var;
    vect[1] = ym - vect[0]*xm;

    // printf("%f, %f", cov, var);
}

void leastSquare(float *x, float *y, int dim, float *vect){
    float sxk = 0,
          syk = 0,
          sxk2 = 0,
          sxkyk = 0;

    for(int k=0; k<dim; k++)
        sxk += x[k];
    for(int k=0; k<dim; k++)
        syk += y[k];
    for(int k=0; k<dim; k++)
        sxk2 += x[k]*x[k];
    for(int k=0; k<dim; k++)
        sxkyk += x[k]*y[k];

    float D = 0,
          Da0 = 0,
          Da1 = 0;
    D = dim * sxk2 - sxk * sxk;
    Da0 = syk * sxk2 - sxkyk * sxk * syk;
    Da1 = dim * sxkyk - syk * sxk;

    vect[0] = Da0 / D;
    vect[1] = Da1 / D;
    printf("%f, %f", vect[0], vect[1]);
}

void adust(float *x, float *y, float *vect, float *U, int n, float alpha){
    FILE *dis = fopen("dis", "w");
    if(dis == NULL) {
		perror("File not found !!!");
		exit(404);
	}

    for(int i = 0; i < n; i++){
        // printf("%f, %f\n", y[i], x[i]);
        fprintf(dis, "%f, %f\n", x[i], y[i]);
    }
    fclose(dis);
    // linLastSq(x, y, n, vect);
    gradient(n, alpha, x, y, vect, U);
}

void get_dataf(int *n, float **x, float **y, float *xmin, float *xmax, float *ymin, float *ymax, float *alpha, float **vect, float **U) {
    *xmin = -1;
    *xmax = 6;
    *ymin = -1.5;
    *ymax = 50;
    *alpha = 0.001;
	float *s = NULL, *z = NULL, *r = NULL, *t = NULL;
	FILE *pf = fopen("data1", "r");
	if(pf == NULL) {
		perror("File not found !!!");
		exit(403);
	}
	
	fscanf(pf, "%d\n", n);
	s = (float*)malloc(sizeof(float*)**n);
	z = (float*)malloc(sizeof(float*)**n);
	r = (float*)malloc(sizeof(float*)*2);
	t = (float*)malloc(sizeof(float*)*2);
	if(s == NULL) {
		perror("Allocation failed!");
		exit(503);
	}
    if(z == NULL) {
		perror("Allocation failed!");
		exit(504);
	}
    if(r == NULL) {
		perror("Allocation failed!");
		exit(505);
	}
	if(t == NULL) {
		perror("Allocation failed!");
		exit(506);
	}
	
	t[0] = 1;
	t[1] = 1;
	
	for(int i = 0; i < *n; i++) {
		fscanf(pf, "%f, %f", &s[i], &z[i]);
	}
	
	*x = s;
    *y = z;
    *vect = r;
    *U = t;
    fclose(pf);
}

void gplotf(float xmin, float xmax, float ymin, float ymax, float *vect, int n){
    FILE *gp = popen("gnuplot -persist", "w");
    if(gp) {        //if gnuplot is found
        fprintf(gp, "set term qt size 960,800\n");
        fprintf(gp, "set title 'Adjustement lineaire'\n");
        fprintf(gp, "set xlabel 'Abscisse'\n");
        fprintf(gp, "set ylabel 'Ordonnee'\n");
        fprintf(gp, "set xrange [%f:%f]\n", xmin, xmax);        
        fprintf(gp, "set yrange [%f:%f]\n", ymin, ymax);
        fprintf(gp, "set loadpath './'\n");
        fprintf(gp, "f(x)=%g*x+%g\n", vect[0], vect[1]);
        fprintf(gp, "plot 'dis', f(x) w l lc 'red' lw 3\n");
        fflush(gp);
        pclose(gp);
    }
}  

