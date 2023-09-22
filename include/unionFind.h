#ifndef UNIONFIND_H
#define UNIONFIND_H

int ufFind(int i, int Id[], int dimension);
void ufInit(int size, int Id[]);
void ufUnion(int p, int q, int Id[], int dimension);

#endif