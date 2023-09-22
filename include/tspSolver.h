#include "../include/unionFind.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"
#include "../include/fileHelpers.h"

#ifndef TSPSPOLVER_H
#define TSPSPOLVER_H

// Função para gerar a Árvore Geradora Mínima (MST) a partir dos vértices e do nome do arquivo de entrada.
void GenerateMST(Vertex *vertices, char* inputFileName, int dimension);

// Função para gerar o tour a partir dos vértices e do nome do arquivo de entrada.
void GenerateTour(Vertex* vertices, char* inputFileName, int dimension);

// Função principal para resolver o Problema do Caixeiro Viajante (TSP) com base no arquivo de entrada.
void SolveTSP(char* inputFileName);

#endif
