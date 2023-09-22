#include "../include/fileHelpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculateDimension(FILE *file) {
  int dimension = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, file)) != EOF) {
    if (strstr(line, "DIMENSION:")) {
      sscanf(line, "DIMENSION: %d", &dimension);
      break;
    }

    free(line);
    line = NULL;
  }

  free(line);

  return dimension;
}

int calculateMaxEdges(int dimension){
  return ((dimension + 1)*dimension)/2;
}

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