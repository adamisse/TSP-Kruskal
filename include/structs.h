#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct city City;
typedef struct edge Edge;

// Define a estrutura de dados para representar uma cidade
struct city {
    int id;
    double x;
    double y;
};

// Define a estrutura de dados para representar uma aresta (conexão entre cidades)
struct edge{
    int city1;
    int city2;
    double distance;
};

#endif