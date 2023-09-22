#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

// Função para calcular a dimensão do problema com base no arquivo de entrada
int calculateDimension(FILE *file);

// Função para calcular o número máximo de arestas possível com base na dimensão
int calculateMaxEdges(int dimension);

// Função para imprimir o cabeçalho para a Árvore Geradora Mínima (MST)
void printMstHeader(FILE *arq, char *fileName, int dimension);

// Função para imprimir o cabeçalho para o tour
void printTourHeader(FILE *arq, char *fileName, int dimension);

#endif
