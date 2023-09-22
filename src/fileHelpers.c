#include "../include/fileHelpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMstHeader(FILE *arq, char *fileName, int dimension) {
  fprintf(arq, "NAME: %s\n", fileName);
  fprintf(arq, "TYPE: MST\n");
  fprintf(arq, "DIMENSION: %d\n", dimension);
  fprintf(arq, "MST_SECTION\n");
}

void printTourHeader(FILE *arq, char *fileName, int dimension) {
  fprintf(arq, "NAME: %s\n", fileName);
  fprintf(arq, "TYPE: TOUR\n");
  fprintf(arq, "DIMENSION: %d\n", dimension);
  fprintf(arq, "TOUR_SECTION\n");
}