#ifndef EDGE_H
#define EDGE_H

// Define a estrutura de dados para representar uma aresta (conexão entre cidades)
struct edge{
    int city1;
    int city2;
    double distance;
};

typedef struct edge Edge;

// Função de comparação para ordenar as arestas pelo comprimento (distância)
int compareEdges(const void *a, const void *b);
void sort(Edge *edges, int edgeCount);

#endif