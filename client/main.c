#include "../include/unionFind.h"
#include "../include/vertex.h"
#include "../include/graph.h"
#include "../include/fileHelpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  FILE *file = fopen(argv[1], "r");

  char *fileName = argv[1];
  strtok(fileName, ".");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int dimension;

  // Ler e analisar as informações do arquivo de entrada
  while ((read = getline(&line, &len, file)) != EOF) {
    if (strstr(line, "DIMENSION:")) {
      sscanf(line, "DIMENSION: %d", &dimension);
      break;
    }
  }

  int maxEdges;

  maxEdges = ((dimension + 1)*dimension)/2;

  Vertex *cities = malloc(dimension * sizeof(Vertex));
  Edge *edges = malloc(maxEdges * sizeof(Edge));

  while ((read = getline(&line, &len, file)) != EOF) {
    if(strcmp(line, "EOF") && strcmp(line, "EOF\n")){
      if(strstr(line, "NODE_COORD_SECTION")) {
        for(int i = 0; i < dimension; i++) {
          char numStr[100];
          fscanf(file, "%d %s", &cities[i].id, numStr);
          cities[i].x = strtod(numStr, NULL);
          //printf("X: %Lf ", cities[i].x);

          fscanf(file, " %s", numStr);

          cities[i].y = strtod(numStr, NULL);
          //printf("Y: %Lf \n", cities[i].y);
        }
      }     
    }
  }

  double** graph = initializeGraph(dimension);

  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      if(i == j){
        graph[i][j] = 9999;
      }
      else{
        graph[i][j] = calculateDistance(cities[i], cities[j]);
      }
    }
  }

  // Calcular as distâncias Euclidianas entre todas as cidades
  int edgeCount = 0;

  for (int i = 0; i < dimension - 1; i++) {
    for (int j = i + 1; j < dimension; j++) {      
      edges[edgeCount].city1 = cities[i].id;
      edges[edgeCount].city2 = cities[j].id;

      double distance = calculateDistance(cities[i], cities[j]);
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
  //printf("Custo total da Árvore Geradora Mínima: %.2lf\n", totalCost);

  fclose(file);
  fclose(outputFile);

  //printf("Arquivo de saída 'saida_mst.txt' gerado com sucesso.\n");

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