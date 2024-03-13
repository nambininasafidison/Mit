#ifndef GAUSS_H
#define GAUSS_H

void triangularisation(float **first_members, float *second_member, int dim);
float *resolution(float **first, float *second,  int dim);
void print(float **matrix, int dim);
void p(float *f);

#endif