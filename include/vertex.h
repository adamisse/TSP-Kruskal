#ifndef VERTEX_H
#define VERTEX_H

struct vertex {
    int id;
    double x;
    double y;
};

typedef struct vertex Vertex;

double calculateDistance(Vertex city1, Vertex city2);

#endif