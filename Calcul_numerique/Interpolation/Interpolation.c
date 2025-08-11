#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gplotf();
int menu();
void choose(int choice,float *step, float *xi);

int main(){
	
/// entrée de données
	printf("Tracage de la courbe d'interpolation\n");
	float 	step = 0.2,
			xi = 6.;

/// Calcul

	while(1){
		choose(menu(), &step, &xi);
        system("killall gnuplot_qt");
		gplotf();
	}

/// Cleanup


    return 0;
}

int menu(){
	int choice;
	
	printf("\n\n\t\t\t\tQue voulez-vous faire?\nTAPER : \n");
	printf("1- Pour tracer la courbe d'interpolation linaire'\n");
	printf("2- Pour tracer la courbe d'interpolation polynomiale\n");
	printf("3- Pour tracer la courbe d'interpolation avec du spline cubique\n");
	printf("0- Pour quiter le programme\n");
	printf("****************************************************\n");
	printf("Entrez votre choix : ");
	scanf("%d",&choice);
	
	return choice;
}

void choose(int choice,float *step, float *xi){
	switch(choice){
		case 1:
			break;
		case 2:
			printf("Entrez le pas de votre choix : ");
			scanf("%f",step);
			break;
		case 3:
			printf("Entrez le point de départ de votre choix : ");
			scanf("%f",xi);
			break;
		default:
            system("killall gnuplot_qt");
			exit(1);
			break;
		
	}
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

void gplotf(){
	FILE *gnuplotPipe = popen("gnuplot -persist","w");
	
	if(gnuplotPipe){
/// Paramètrage de gnuplot
		fprintf(gnuplotPipe,"set term qt size 800,600\n");
		fprintf(gnuplotPipe,"set title 'TITRE'\n");
		fprintf(gnuplotPipe,"set xlabel 'x'\n");
		fprintf(gnuplotPipe,"set ylabel 'y'\n");
		fprintf(gnuplotPipe,"set yzeroaxis\n");
		fprintf(gnuplotPipe,"set xzeroaxis\n");
		fprintf(gnuplotPipe,"set xrange [%f:%f]\n",-6.,8.);
		fprintf(gnuplotPipe, "set loadpath 'E:'\n");
		fprintf(gnuplotPipe,"set yrange [%f:%f]\n",-2.,5.);
		fprintf(gnuplotPipe,"f(x)=(x*x*cos(x)-x)/10\n");
		fprintf(gnuplotPipe,"plot 'data' using 1:2 with linespoints pt 7 ps 2 lc 'blue' lw 3\n");
		
		fflush(gnuplotPipe);
		pclose(gnuplotPipe);
	}
}
