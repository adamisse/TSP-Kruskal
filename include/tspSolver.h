#include "../include/unionFind.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"
#include "../include/fileHelpers.h"

#ifndef TSPSPOLVER_H
#define TSPSPOLVER_H

void GenerateMST(Vertex *vertices, char* inputFileName, int dimension);
void GenerateTour(Vertex* vertices, char* inputFileName, int dimension);
void SolveTSP(char* inputFileName);

#endif