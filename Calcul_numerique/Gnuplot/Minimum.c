#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gplotf();
int menu();
void choose(int choice,float *step, float *xi);

float f(float x);
float Df(float x);
void gradient(float alpha, float xi);


int main(){
	
/// entrée de données
	printf("Recherche de minimum en dimension 1 avec la descente du gradient\n");
	float 	step = 0.2,
			xi = 6.;

/// Calcul

	while(1){
		printf("Pas = %f , point initial = %f\n",step,xi);
		choose(menu(), &step, &xi);
        system("killall gnuplot_qt");
		gradient(step, xi);
		gplotf();
	}

/// Cleanup


    return 0;
}

int menu(){
	int choice;
	
	printf("\n\n\t\t\t\tQue voulez-vous faire?\nTAPER : \n");
	printf("1- Pour tracer la courbe\n");
	printf("2- Pour changer le pas\n");
	printf("3- Pour changer le point initial\n");
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

float f(float x){
	return (x*x*cos(x)-x)/10;
}

float Df(float x){
	x = (2*x*cos(x) - x*x *sin(x) -1)/10;
	return x;
}

void gradient(float alpha, float xi){
	FILE *pf = fopen("data2","w");
	if(pf == NULL) printf("Erreur lor de l'ouverture\n\n");
	float a = xi;
	int count = 1;
	float a1=0;
	
	a1 = a - alpha*Df(a);
	
	while(fabs(a-a1)>1e-7){
		a = a1;
		fprintf(pf,"%f, %f\n",a,f(a));
		a1 = a - alpha*Df(a);
		count++;
	}
	
	xi = a;
	
	fclose(pf);
	
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
		fprintf(gnuplotPipe,"plot 'data2' using 1:2 with linespoints pt 7 ps 1 lc 'blue' lw 3, f(x) w l lc 'purple' lw 1\n");
		
		fflush(gnuplotPipe);
		pclose(gnuplotPipe);
	}
}