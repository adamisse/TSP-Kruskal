#include "../include/vertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a estrutura de dados para representar uma cidade

double calculateDistance(Vertex city1, Vertex city2) {
  double dx = city1.x - city2.x;
  double dy = city1.y - city2.y;
  
  double sqrt1 = sqrt(dx * dx + dy * dy);

  return sqrt1;
}