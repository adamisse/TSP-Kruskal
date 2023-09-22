#include "../include/edge.h"
#include <stdlib.h>
#include <stdio.h>

int compareEdges(const void *a, const void *b) {
  if ((*(Edge *)a).distance < (*(Edge *)b).distance)
    return -1;
  if ((*(Edge *)a).distance > (*(Edge *)b).distance)
    return 1;
  return 0;
}

void sort(Edge *edges, int edgeCount) {
  qsort(edges, edgeCount, sizeof(Edge), compareEdges);
}