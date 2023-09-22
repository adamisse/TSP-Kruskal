#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

double **initializeGraph(int size);
void DFS(double **graph, int *visited, int vertex, int dimension, FILE *tourFIle);
void freeGraph(double **graph, int size);

#endif