#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defina a estrutura de dados para representar uma cidade

// Defina a estrutura de dados para representar uma aresta (conexão entre
// cidades)

// Função para calcular a distância Euclidiana entre duas cidades

// Função de comparação para ordenar as arestas pelo comprimento (distância)


// Estrutura para representar um conjunto disjunto (Union-Find)

// Função para inicializar o conjunto disjunto

// Função para encontrar o representante de um conjunto (compressão de caminho)


// Função para unir dois conjuntos

int main() {
  FILE *file = fopen("berlin52.tsp", "r");
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

  City cities[dimension];

  int maxEdges;

  maxEdges = ((dimension + 1)*dimension)/2;

  Edge edges[maxEdges];

  while ((read = getline(&line, &len, file)) != EOF) {
    if(strcmp(line, "EOF") && strcmp(line, "EOF\n")){
      if(strstr(line, "NODE_COORD_SECTION")) {
        for(int i = 0; i < dimension; i++) {
          fscanf(file, "%d %lf %lf", &cities[i].id, &cities[i].x, &cities[i].y);
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
  //graph[0][0] = 9999;
  for (int i = 0; i < dimension - 1; i++) {
    for (int j = i + 1; j < dimension; j++) {
      //graph[j][j] = 9999;
      edges[edgeCount].city1 = cities[i].id;
      edges[edgeCount].city2 = cities[j].id;
      double distance = calculateDistance(cities[i], cities[j]);
      //graph[i][j] = distance;
      edges[edgeCount].distance = distance;
      edgeCount++;
    }
  }

  // Ordenar as arestas pelo comprimento (distância)
  sort(edges, edgeCount);

  // Crie um conjunto disjunto para rastrear conjuntos de cidades na árvore
  DisjointSet *set = initializeSet(dimension);

  // Inicialize variáveis para controlar o número de arestas na árvore
  int edgesInTree = 0;

  // Inicialize uma variável para armazenar o custo total da árvore geradora
  // mínima
  double totalCost = 0.0;

  // Crie um arquivo de saída para armazenar as arestas da árvore geradora
  // mínima
  FILE *outputFile = fopen("saida_mst.txt", "w");
  if (outputFile == NULL) {
    printf("Erro ao criar o arquivo de saída.\n");
    return 1;
  }

  // Escreva os cabeçalhos no arquivo de saída
  fprintf(outputFile, "NAME: berlin52\n");
  fprintf(outputFile, "TYPE: MST\n");
  fprintf(outputFile, "DIMENSION: %d\n", dimension);
  fprintf(outputFile, "MST_SECTION\n");

  // Encontre a árvore geradora mínima usando o algoritmo de Kruskal
  for (int i = 0; i < edgeCount; i++) {
    int city1 = edges[i].city1;
    int city2 = edges[i].city2;
    int root1 = find(set, city1);
    int root2 = find(set, city2);

    // Verifique se adicionar esta aresta não criará um ciclo
    if (root1 != root2) {
      fprintf(outputFile, "%d %d\n", city1, city2);
      totalCost += edges[i].distance;
      unionSets(set, root1, root2);
      edgesInTree++;

      // Se todas as cidades estiverem na árvore, pare
      if (edgesInTree == dimension - 1) {
        break;
      }
    }
  }

  // Escreva o custo total da árvore geradora mínima no arquivo de saída
  fprintf(outputFile, "EOF\nCusto total da Árvore Geradora Mínima: %.2lf\n",
          totalCost);

  fclose(file);
  fclose(outputFile);

  printf("Arquivo de saída 'saida_mst.txt' gerado com sucesso.\n");

  int *visited = malloc(sizeof(int) * dimension);
  for(int i = 0; i < dimension; i++){
    visited[i] = 0;
  }

  DFS(graph, visited, 0, dimension);
  // Libere a memória alocada para o conjunto disjunto
  freeDisjoint(set);
  free(set);

  return 0;
}