#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct city City;
typedef struct edge Edge;
typedef struct disjointset DisjointSet;

struct city {
    int id;
    double x;
    double y;
};

struct edge{
    int city1;
    int city2;
    double distance;
};

struct disjointset{
    int *parent;
};

#endif