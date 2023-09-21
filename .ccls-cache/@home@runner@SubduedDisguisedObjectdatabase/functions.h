#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

double calculateDistance(City city1, City city2);

double **initializeGraph(int size);

DisjointSet *initializeSet(int size);

int compareEdges(const void *a, const void *b);

int find(DisjointSet *set, int element);

void unionSets(DisjointSet *set, int element1, int element2);

void freeDisjoint(DisjointSet *set);

void sort(Edge *edges, int edgeCount);

void DFS(double **graph, int *visited, int vertex, int dimension);

#endif