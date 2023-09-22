#ifndef UNIONFIND_H
#define UNIONFIND_H

// Função para encontrar o conjunto (grupo) ao qual um elemento pertence.
int ufFind(int i, int Id[], int dimension);

// Função para inicializar a estrutura de dados de Union-Find com o tamanho especificado.
void ufInit(int size, int Id[]);

// Função para unir dois conjuntos (grupos) diferentes em um único conjunto.
void ufUnion(int p, int q, int Id[], int dimension);

#endif
