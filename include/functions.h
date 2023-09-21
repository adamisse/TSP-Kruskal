#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"
#include <stdio.h>

// Função para calcular a distância Euclidiana entre duas cidades
double calculateDistance(City city1, City city2);

double **initializeGraph(int size);

int ufFind(int i, int Id[]);

void ufInit(int size, int Id[]);

void ufUnion(int p, int q, int Id[]);

// Função de comparação para ordenar as arestas pelo comprimento (distância)
int compareEdges(const void *a, const void *b);

void sort(Edge *edges, int edgeCount);

void DFS(double **graph, int *visited, int vertex, int dimension,
         FILE *tourFIle);

void printMstHeader(FILE *arq, char *fileName, int dimension);
void printTourHeader(FILE *arq, char *fileName, int dimension);

#endif