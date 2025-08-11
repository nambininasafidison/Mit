#include <stdio.h>
#include <stdlib.h>

// void gplot(float ymin, float ymax);
void gplotf(float ymin, float ymax);

int main(){
    printf("Trace de courbes avec gnuplot\n");

    float ymin = -1.5, ymax = 1.5;

    // gplot(ymin, ymax);
    gplotf(ymin, ymax);

    return 0;
}

void gplotf(float ymin, float ymax){
    FILE *gp = popen("gnuplot -persist", "w");
    if(gp) {        //if gnuplot is found
        fprintf(gp, "set term qt size 960,800\n");
        fprintf(gp, "set title 'Titre'\n");
        fprintf(gp, "set xlabel 'Temps (s)'\n");
        fprintf(gp, "set ylabel 'Valeurs'\n");
        fprintf(gp, "set yrange [%f:%f]\n", ymin, ymax);
        fprintf(gp, "set loadpath './'\n");
        fprintf(gp, "plot 'data' w lp pt 14 lt 3 lw 2 lc 'red', sin(x), cos(x)\n");
        fflush(gp);
        pclose(gp);
    }
}  

// void gplot(float ymin, float ymax){
//     FILE *gp = popen("gnuplot -persist", "w");
//     if(gp) {        //if gnuplot is found
//         fprintf(gp, "set term qt size 960,800\n");
//         fprintf(gp, "set title 'Titre'\n");
//         fprintf(gp, "set xlabel 'Temps (s)'\n");
//         fprintf(gp, "set ylabel 'Valeurs'\n");
//         fprintf(gp, "set yrange [%f:%f]\n", ymin, ymax);
//         fprintf(gp, "plot sin(x), cos(x)\n");
//         fflush(gp);
//         pclose(gp);
//     }
// }       

