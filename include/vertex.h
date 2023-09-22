#include <stdio.h>
#include <stdlib.h>

#ifndef VERTEX_H
#define VERTEX_H

struct vertex {
    int id;
    double x;
    double y;
};

typedef struct vertex Vertex;

double calculateDistanceBetweenVertices(Vertex city1, Vertex city2);
Vertex* StoreVerticesFromInputFile(FILE* inputFile, int dimension);

#endif