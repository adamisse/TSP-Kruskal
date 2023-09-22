#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

double **initializeGraph(int size);
void DFS(double **graph, int *visited, int vertex, int dimension, FILE *tourFIle);

#endif