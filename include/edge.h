#ifndef EDGE_H
#define EDGE_H

// Struct representando uma aresta entre duas cidades, com a distância entre elas.
struct edge {
    int city1;     
    int city2;
    double distance;
};

typedef struct edge Edge;

// Função para ordenar um array de arestas com base na distância.
void sort(Edge *edges, int edgeCount);

// Função interna para realizar a ordenação personalizada de arestas (QuickSort personalizado).
void edgeCustomQuickSort(Edge *edges, int lo, int hi);

// Função auxiliar do QuickSort personalizado para dividir o array.
int partition(Edge *edges, int lo, int hi);

#endif
