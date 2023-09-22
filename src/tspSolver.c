#include "../include/tspSolver.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void SolveTSP(char* inputFileName){
  FILE *inputFile = fopen(inputFileName, "r");
  strtok(inputFileName, ".");

  if (inputFile == NULL) {
    printf("Error opening file.");
    return;
  }

  int dimension = calculateDimension(inputFile);
  Vertex* vertices = StoreVerticesFromInputFile(inputFile, dimension);
  
  fclose(inputFile);

  GenerateMST(vertices, inputFileName, dimension);
  GenerateTour(vertices, inputFileName, dimension);
}

void GenerateMST(Vertex *vertices, char* inputFileName, int dimension){
  int maxEdges = calculateMaxEdges(dimension);

  Edge *edges = malloc(maxEdges * sizeof(Edge));

  // Calcular as distâncias Euclidianas entre todas as cidades
  int edgeCount = 0;

  for (int i = 0; i < dimension - 1; i++) {
    for (int j = i + 1; j < dimension; j++) {      
      edges[edgeCount].city1 = vertices[i].id;
      edges[edgeCount].city2 = vertices[j].id;

      double distance = calculateDistanceBetweenVertices(vertices[i], vertices[j]);
      edges[edgeCount].distance = distance;
      
      edgeCount++;
    }
  }

  // Ordenar as arestas pelo comprimento (distância)
  sort(edges, edgeCount);
  int id[dimension + 1];
  ufInit(dimension + 1, id);

  // Inicialize variáveis para controlar o número de arestas na árvore
  int edgesInTree = 0;

  // Crie um arquivo de saída para armazenar as arestas da árvore geradora
  // mínima

  char mstFileName[100];
  strcpy(mstFileName, inputFileName);
  strcat(mstFileName, ".mst");

  FILE *outputFile = fopen(mstFileName, "w");
  if (outputFile == NULL) {
    printf("Error creating file.");
    return;
  }

  // Escreva os cabeçalhos no arquivo de saída
  printMstHeader(outputFile, inputFileName, dimension);
  
  // Encontre a árvore geradora mínima usando o algoritmo de Kruskal
  for (int i = 0; i < edgeCount; i++) {
    int city1 = edges[i].city1;
    int city2 = edges[i].city2;

    int root1 = ufFind(city1, id, dimension);
    int root2 = ufFind(city2, id, dimension);

    // Verifique se adicionar esta aresta não criará um ciclo
    if (root1 != root2) {
      fprintf(outputFile, "%d %d\n", city1, city2);
      ufUnion(city1, city2, id, dimension);
      edgesInTree++;

      // Se todas as cidades estiverem na árvore, pare
      if (edgesInTree == dimension - 1) {
        break;
      }
    }
  }

  fprintf(outputFile, "EOF\n");
  fclose(outputFile);
}

void GenerateTour(Vertex* vertices, char* inputFileName, int dimension){  
  int *visited = malloc(sizeof(int) * dimension);
  for(int i = 0; i < dimension; i++){
    visited[i] = 0;
  }

  char tourFileName[100];
  strcpy(tourFileName, inputFileName);
  strcat(tourFileName, ".tour");

  FILE *tourFile = fopen(tourFileName, "w");
  if (tourFile == NULL) {
    printf("Error creating file.");
    return;
  }

  printTourHeader(tourFile, inputFileName, dimension);

  double** graph = initializeGraph(dimension);

  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      if(i == j){
        graph[i][j] = 9999;
      }
      else{
        graph[i][j] = calculateDistanceBetweenVertices(vertices[i], vertices[j]);
      }
    }
  }

  DFS(graph, visited, 0, dimension, tourFile);

  fprintf(tourFile, "EOF\n");
  fclose(tourFile);
}