#include "../include/tspSolver.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

  free(vertices);
}

void GenerateMST(Vertex *vertices, char* inputFileName, int dimension){
  clock_t startTime = clock();

  int maxEdges = calculateMaxEdges(dimension);

  Edge *edges = malloc(maxEdges * sizeof(Edge));
  int id[dimension + 1];

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

  clock_t startTime3 = clock();

  // Ordenar as arestas pelo comprimento (distância)
  sort(edges, edgeCount);

  clock_t endTime3 = clock();
  double executionTime3 = (double)(endTime3 - startTime3) / CLOCKS_PER_SEC;
  printf("SORT execution time: %.4f seconds\n", executionTime3);

  ufInit(dimension + 1, id);

  // Inicialize variáveis para controlar o número de arestas na árvore
  int edgesInTree = 0;

  // Crie um arquivo de saída para armazenar as arestas da árvore geradora
  // mínima

  char mstFileName[100];
  strcpy(mstFileName, inputFileName);
  strcat(mstFileName, ".mst");

  FILE *mstFile = fopen(mstFileName, "w");
  if (mstFile == NULL) {
    printf("Error creating file.");
    return;
  }

  // Escreva os cabeçalhos no arquivo de saída
  printMstHeader(mstFile, inputFileName, dimension);
  
  
  clock_t startTime2 = clock();
  // Encontre a árvore geradora mínima usando o algoritmo de Kruskal
  for (int i = 0; i < edgeCount; i++) {
    int city1 = edges[i].city1;
    int city2 = edges[i].city2;

    int root1 = ufFind(city1, id, dimension);
    int root2 = ufFind(city2, id, dimension);

    // Verifique se adicionar esta aresta não criará um ciclo
    if (root1 != root2) {
      fprintf(mstFile, "%d %d\n", city1, city2);
      ufUnion(city1, city2, id, dimension);
      edgesInTree++;

      // Se todas as cidades estiverem na árvore, pare
      if (edgesInTree == dimension - 1) {
        break;
      }
    }
  }

  clock_t endTime2 = clock();
  double executionTime2 = (double)(endTime2 - startTime2) / CLOCKS_PER_SEC;

  printf("Kruskal execution time: %.4f seconds\n", executionTime2);

  free(edges);

  fprintf(mstFile, "EOF\n");
  fclose(mstFile);

  clock_t endTime = clock();
  double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

  printf("Generate MST execution time: %.4f seconds\n", executionTime);
}

void GenerateTour(Vertex* vertices, char* inputFileName, int dimension){  
  clock_t startTime = clock();

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
  
  freeGraph(graph, dimension);
  free(visited);

  fprintf(tourFile, "EOF\n");
  fclose(tourFile);

  clock_t endTime = clock();
  double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

  printf("GenerateTour execution time: %.4f seconds\n", executionTime);
}