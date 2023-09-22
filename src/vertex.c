#include "../include/vertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define a estrutura de dados para representar uma cidade

double calculateDistanceBetweenVertices(Vertex city1, Vertex city2) {
  double dx = city1.x - city2.x;
  double dy = city1.y - city2.y;
  
  double sqrt1 = sqrt(dx * dx + dy * dy);

  return sqrt1;
}

Vertex* StoreVerticesFromInputFile(FILE* inputFile, int dimension){
  Vertex *cities = malloc(dimension * sizeof(Vertex));

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, inputFile)) != EOF) {
    if(strcmp(line, "EOF") && strcmp(line, "EOF\n")){
      if(strstr(line, "NODE_COORD_SECTION")) {
        for(int i = 0; i < dimension; i++) {
          char numStr[100];
          fscanf(inputFile, "%d %s", &cities[i].id, numStr);
          cities[i].x = strtod(numStr, NULL);

          fscanf(inputFile, " %s", numStr);

          cities[i].y = strtod(numStr, NULL);
        }
      }     
    }
  }

  return cities;
}