#include <stdio.h>
#include <stdlib.h>

#ifndef VERTEX_H
#define VERTEX_H

// Struct representando um vértice do grafo com um id e suas coordenadas (x, y).
struct vertex {
    int id;     // Identificador do vértice
    double x;   // Coordenada x do vértice
    double y;   // Coordenada y do vértice
};

typedef struct vertex Vertex;

// Função para calcular a distância euclidiana entre dois vértices (cidades) usando suas coordenadas.
double calculateDistanceBetweenVertices(Vertex city1, Vertex city2);

// Função para armazenar os vértices a partir de um arquivo de entrada e retornar um array de vértices.
Vertex* StoreVerticesFromInputFile(FILE* inputFile, int dimension);

#endif
