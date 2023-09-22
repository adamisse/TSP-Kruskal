#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

int calculateDimension(FILE *file);
int calculateMaxEdges(int dimension);

void printMstHeader(FILE *arq, char *fileName, int dimension);
void printTourHeader(FILE *arq, char *fileName, int dimension);

#endif