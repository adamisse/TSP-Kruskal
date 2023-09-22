#include "../include/unionFind.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"
#include "../include/fileHelpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  FILE *inputFile = fopen(argv[1], "r");

  char *fileName = argv[1];
  strtok(fileName, ".");

  if (inputFile == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }

  int dimension = calculateDimension(inputFile);
  int maxEdges = calculateMaxEdges(dimension);

  Vertex *vertices = StoreVerticesFromInputFile(inputFile, dimension);
  Edge *edges = malloc(maxEdges * sizeof(Edge));

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

  int Id[dimension + 1];

  ufInit(dimension + 1, Id);

  // Inicialize variáveis para controlar o número de arestas na árvore
  int edgesInTree = 0;

  // Inicialize uma variável para armazenar o custo total da árvore geradora
  // mínima
  double totalCost = 0.0;

  // Crie um arquivo de saída para armazenar as arestas da árvore geradora
  // mínima

  char mstFileName[100];
  strcpy(mstFileName, fileName);
  strcat(mstFileName, ".mst");

  FILE *outputFile = fopen(mstFileName, "w");
  if (outputFile == NULL) {
    printf("Erro ao criar o arquivo de saída.\n");
    return 1;
  }

  // Escreva os cabeçalhos no arquivo de saída
  printMstHeader(outputFile, fileName, dimension);
  
  // Encontre a árvore geradora mínima usando o algoritmo de Kruskal
  for (int i = 0; i < edgeCount; i++) {
    int city1 = edges[i].city1;
    int city2 = edges[i].city2;

    //printf("\nUF City1: %d - Id: %d\n", city1, Id[city1]);
    int root1 = ufFind(city1, Id, dimension);
    //printf("\n");

    //printf("UF City2: %d - Id: %d\n\n", city2, Id[city2]);
    int root2 = ufFind(city2, Id, dimension);

    // Verifique se adicionar esta aresta não criará um ciclo
    if (root1 != root2) {
      fprintf(outputFile, "%d %d\n", city1, city2);
      totalCost += edges[i].distance;
      ufUnion(city1, city2, Id, dimension);
      edgesInTree++;

      // Se todas as cidades estiverem na árvore, pare
      if (edgesInTree == dimension - 1) {
        break;
      }
    }
  }

  fprintf(outputFile, "EOF\n");

  fclose(inputFile);
  fclose(outputFile);

  int *visited = malloc(sizeof(int) * dimension);
  for(int i = 0; i < dimension; i++){
    visited[i] = 0;
  }

  char tourFileName[100];
  strcpy(tourFileName, fileName);
  strcat(tourFileName, ".tour");

  FILE *tourFile = fopen(tourFileName, "w");
  if (tourFile == NULL) {
    printf("Erro ao criar o arquivo de saída.\n");
    return 1;
  }

  printTourHeader(tourFile, fileName, dimension);
  DFS(graph, visited, 0, dimension, tourFile);
  fprintf(tourFile, "EOF\n");
  fclose(tourFile);

  return 0;
}