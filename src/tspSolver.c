#include "../include/tspSolver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Função para resolver o Problema do Caixeiro Viajante (TSP) a partir de um arquivo de entrada.
void SolveTSP(char* inputFileName) {
  // Abre o arquivo de entrada para leitura.
  FILE *inputFile = fopen(inputFileName, "r");
  strtok(inputFileName, ".");

  if (inputFile == NULL) {
    printf("Error opening file.");
    return;
  }

  // Calcula a dimensão do problema a partir do arquivo.
  int dimension = calculateDimension(inputFile);

  // Lê as informações das cidades a partir do arquivo de entrada.
  Vertex* vertices = StoreVerticesFromInputFile(inputFile, dimension);
  
  fclose(inputFile);

  // Gera a Árvore Geradora Mínima (MST).
  GenerateMST(vertices, inputFileName, dimension);

  // Gera o tour com base na MST.
  GenerateTour(vertices, inputFileName, dimension);

  // Libera a memória alocada para o array de vértices.
  free(vertices);
}

// Função para gerar a Árvore Geradora Mínima (MST) a partir dos vértices e escrevê-la em um arquivo.
void GenerateMST(Vertex *vertices, char* inputFileName, int dimension) {
  // Inicia o relógio para medir o tempo de execução.
  clock_t startTime = clock();

  // Calcula o número máximo de arestas com base na dimensão do problema.
  int maxEdges = calculateMaxEdges(dimension);

  // Aloca memória para armazenar as arestas.
  Edge *edges = malloc(maxEdges * sizeof(Edge));
  int id[dimension + 1];

  // Calcula as distâncias Euclidianas entre todas as cidades e preenche as arestas.
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

  // Ordena as arestas pelo comprimento (distância).
  sort(edges, edgeCount);

  // Inicializa a estrutura Union-Find para controlar a conexão das cidades.
  ufInit(dimension + 1, id);

  // Inicializa variáveis para controlar o número de arestas na árvore.
  int edgesInTree = 0;

  // Cria um arquivo de saída para armazenar as arestas da MST.
  char mstFileName[100];
  strcpy(mstFileName, inputFileName);
  strcat(mstFileName, ".mst");

  FILE *mstFile = fopen(mstFileName, "w");
  if (mstFile == NULL) {
    printf("Error creating file.");
    return;
  }

  // Escreve os cabeçalhos no arquivo de saída.
  printMstHeader(mstFile, inputFileName, dimension);
  
  // Encontra a Árvore Geradora Mínima (MST) usando o algoritmo de Kruskal.
  for (int i = 0; i < edgeCount; i++) {
    int city1 = edges[i].city1;
    int city2 = edges[i].city2;

    int root1 = ufFind(city1, id, dimension);
    int root2 = ufFind(city2, id, dimension);

    // Verifica se adicionar esta aresta não criará um ciclo.
    if (root1 != root2) {
      fprintf(mstFile, "%d %d\n", city1, city2);
      ufUnion(city1, city2, id, dimension);
      edgesInTree++;

      // Se todas as cidades estiverem na árvore, pare.
      if (edgesInTree == dimension - 1) {
        break;
      }
    }
  }

  free(edges);

  fprintf(mstFile, "EOF\n");
  fclose(mstFile);

  // Finaliza o relógio e calcula o tempo de execução.
  clock_t endTime = clock();
  double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

  //printf("Generate MST execution time: %.4f seconds\n", executionTime);
}

// Função para gerar o tour a partir da MST e escrevê-lo em um arquivo.
void GenerateTour(Vertex* vertices, char* inputFileName, int dimension) {  
  // Inicia o relógio para medir o tempo de execução.
  clock_t startTime = clock();

  // Aloca um array para rastrear quais cidades foram visitadas durante o tour.
  int *visited = malloc(sizeof(int) * dimension);
  for(int i = 0; i < dimension; i++){
    visited[i] = 0;
  }

  // Cria um arquivo de saída para armazenar o tour.
  char tourFileName[100];
  strcpy(tourFileName, inputFileName);
  strcat(tourFileName, ".tour");

  FILE *tourFile = fopen(tourFileName, "w");
  if (tourFile == NULL) {
    printf("Error creating file.");
    return;
  }

  // Escreve os cabeçalhos no arquivo de saída.
  printTourHeader(tourFile, inputFileName, dimension);

  // Inicializa uma matriz de distâncias entre as cidades.
  double** graph = initializeGraph(dimension);

  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      if(i == j){
        graph[i][j] = 9999; // Valor arbitrário para representar a ausência de uma aresta.
      }
      else{
        graph[i][j] = calculateDistanceBetweenVertices(vertices[i], vertices[j]);
      }
    }
  }

  // Inicia o passeio (tour) a partir da cidade 0 usando a DFS.
  DFS(graph, visited, 0, dimension, tourFile);
  
  // Libera a memória alocada para a matriz de distâncias e o array de visitados.
  freeGraph(graph, dimension);
  free(visited);

  fprintf(tourFile, "EOF\n");
  fclose(tourFile);

  // Finaliza o relógio e calcula o tempo de execução.
  clock_t endTime = clock();
  double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

  //printf("GenerateTour execution time: %.4f seconds\n", executionTime);
}
