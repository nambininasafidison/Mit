#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define eps 1e-6

void get_dataf(int *n, float **x, float **y, float *xmin, float *xmax, float *ymin, float *ymax, float *alpha, float **vect, float **vect1, float **U);
void gplotf(float xmin, float xmax, float ymin, float ymax, float *vect, float *vect1, int n);
float D0(int n, float *x, float *y, float a, float b);
float D1(int n, float *x, float *y, float a, float b);
void adust(float *x, float *y, float *vect, float *vect1, float *U, int n, float alpha, float xmin, float xmax, float ymin, float ymax);
void gradient(int n, float alpha, float *x, float *y, float *vect, float *vect1, float *U, float xmin, float xmax, float ymin, float ymax);


int main(){
    printf("Trace de courbes avec gnuplot\n");

/// Data intilisation
    int n = 0;
    float *vect = NULL, *vect1 = NULL, *U = NULL, xmin = 0, xmax = 0, ymin = -1.5, ymax = 50, alpha = 0, *x = NULL, *y = NULL;

/// Get data
    get_dataf(&n,  &x, &y, &xmin, &xmax, &ymin, &ymax, &alpha, &vect, &vect1, &U);

/// Linear adjustement
    adust(x, y, vect, vect1, U, n, alpha, xmin, xmax, ymin, ymax);

/// Display with gnuplot
    gplotf(xmin, xmax, ymin, ymax, vect, vect1, n);


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

void gradient(int n, float alpha, float *x, float *y, float *vect, float *vect1, float *U, float xmin, float xmax, float ymin, float ymax){
    float a = U[0], b = U[1];
    float 
		an1 = a - (alpha * D0(n, x, y, a, b)),
        bn1 = b - (alpha * D1(n, x, y, a, b));
    int i = 0, j = 0;
    while(fabs( a - an1 ) + fabs( b - bn1 ) > 1e-6){
        i++;
        a = an1;
        b= bn1;
        an1 = a - (alpha * D0(n, x, y, a, b));
        bn1 = b - (alpha * D1(n, x, y, a, b));
        if ( i == 1 || i == 4 || i == 10 || i == 250) {
            vect[j] = b;
            vect1[j] = a;
            j++;
        }
    }
    vect[j] = b;
    vect1[j] = a;
}

void adust(float *x, float *y, float *vect, float *vect1, float *U, int n, float alpha, float xmin, float xmax, float ymin, float ymax){
    FILE *dis = fopen("dis", "w");
    if(dis == NULL) {
		perror("File not found !!!");
		exit(404);
	}

    for(int i = 0; i < n; i++){
        fprintf(dis, "%f, %f\n", x[i], y[i]);
    }
    fclose(dis);
    gradient(n, alpha, x, y, vect, vect1, U, xmin, xmax, ymin, ymax);
}

void get_dataf(int *n, float **x, float **y, float *xmin, float *xmax, float *ymin, float *ymax, float *alpha, float **vect, float **vect1, float **U) {
    *xmin = -1;
    *xmax = 6;
    *ymin = -1.5;
    *ymax = 50;
    *alpha = 0.001;
	float *s = NULL, *z = NULL, *r = NULL, *t = NULL, *u = NULL;
	FILE *pf = fopen("data1", "r");
	if(pf == NULL) {
		perror("File not found !!!");
		exit(403);
	}
	
	fscanf(pf, "%d\n", n);
	s = (float*)malloc(sizeof(float)**n);
	z = (float*)malloc(sizeof(float)**n);
	r = (float*)calloc(2000, sizeof(float));
	t = (float*)malloc(sizeof(float)*2);
	u = (float*)calloc(2000, sizeof(float));
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
    if(u == NULL) {
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
    *vect1 = u;
    *U = t;
    fclose(pf);
}

void gplotf(float xmin, float xmax, float ymin, float ymax, float *vect, float *vect1, int n){
    FILE *gp = popen("gnuplot -persist", "w");
    char* courbe = NULL;
    courbe = (char*)malloc(255000000);
    if(courbe == NULL) printf("Erreur d'allocation");
    int i=0;
    if(gp) {        //if gnuplot is found
        fprintf(gp, "set term qt size 960,800\n");
        fprintf(gp, "set title 'Adjustement lineaire'\n");
        fprintf(gp, "set xlabel 'Abscisse'\n");
        fprintf(gp, "set ylabel 'Ordonnee'\n");
        fprintf(gp, "set key top left\n");
        fprintf(gp, "set xrange [%f:%f]\n", xmin, xmax);        
        fprintf(gp, "set yrange [%f:%f]\n", ymin, ymax);
        fprintf(gp, "set loadpath './'\n");
        while (vect[i] != 0.0 && vect1[i] != 0.0)
        {
            fprintf(gp, "f%d(x)=%g*x+%g\n", i, vect[i], vect1[i]);
            char tmp[255];
            char color[5][10] = {"green", "blue", "black", "cyan", "pink"};
            sprintf(tmp, " f%d(x) w l lc '%s' lw 2,", i, color[i]);
            strcat(courbe,tmp);
            i++;
        }
        fprintf(gp, "g(x)=%g*x+%g\n", vect[i-1], vect1[i-1]);
        fprintf(gp, "plot 'dis' pt 13 ps 2 lc 'blue',%s g(x) w l lc 'red' lw 3\n", courbe);
        fflush(gp);
        pclose(gp);
    }
}  

