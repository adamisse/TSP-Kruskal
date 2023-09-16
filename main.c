#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Defina a estrutura de dados para representar uma cidade
typedef struct {
    int id;
    double x;
    double y;
} City;

// Defina a estrutura de dados para representar uma aresta (conexão entre cidades)
typedef struct {
    int city1;
    int city2;
    double distance;
} Edge;

// Função para calcular a distância Euclidiana entre duas cidades
double calculateDistance(City city1, City city2) {
    double dx = city1.x - city2.x;
    double dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

// Função de comparação para ordenar as arestas pelo comprimento (distância)
int compareEdges(const void *a, const void *b) {
    if ((*(Edge *)a).distance < (*(Edge *)b).distance) return -1;
    if ((*(Edge *)a).distance > (*(Edge *)b).distance) return 1;
    return 0;
}

// Estrutura para representar um conjunto disjunto (Union-Find)
typedef struct {
    int *parent;
} DisjointSet;

// Função para inicializar o conjunto disjunto
DisjointSet *initializeSet(int size) {
    DisjointSet *set = (DisjointSet *)malloc(sizeof(DisjointSet));
    set->parent = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        set->parent[i] = i;
    }
    return set;
}

// Função para encontrar o representante de um conjunto (compressão de caminho)
int find(DisjointSet *set, int element) {
    if (set->parent[element] != element) {
        set->parent[element] = find(set, set->parent[element]);
    }
    return set->parent[element];
}

// Função para unir dois conjuntos
void unionSets(DisjointSet *set, int element1, int element2) {
    int root1 = find(set, element1);
    int root2 = find(set, element2);
    if (root1 != root2) {
        set->parent[root1] = root2;
    }
}

int main() {
    FILE *file = fopen("in/berlin52.tsp", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    char line[100];
    int dimension;
    City cities[52];
    Edge edges[1326]; // 52 * 51 / 2, número máximo de arestas para 52 cidades

    // Ler e analisar as informações do arquivo de entrada
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "DIMENSION:")) {
            sscanf(line, "DIMENSION: %d", &dimension);
        } else if (strstr(line, "NODE_COORD_SECTION")) {
            for (int i = 0; i < dimension; i++) {
                fscanf(file, "%d %lf %lf", &cities[i].id, &cities[i].x, &cities[i].y);
            }
        }
    }

    // Calcular as distâncias Euclidianas entre todas as cidades
    int edgeCount = 0;
    for (int i = 0; i < dimension - 1; i++) {
        for (int j = i + 1; j < dimension; j++) {
            edges[edgeCount].city1 = cities[i].id;
            edges[edgeCount].city2 = cities[j].id;
            edges[edgeCount].distance = calculateDistance(cities[i], cities[j]);
            edgeCount++;
        }
    }

    // Ordenar as arestas pelo comprimento (distância)
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    // Crie um conjunto disjunto para rastrear conjuntos de cidades na árvore
    DisjointSet *set = initializeSet(dimension);

    // Inicialize variáveis para controlar o número de arestas na árvore
    int edgesInTree = 0;

    // Inicialize uma variável para armazenar o custo total da árvore geradora mínima
    double totalCost = 0.0;

    // Crie um arquivo de saída para armazenar as arestas da árvore geradora mínima
    FILE *outputFile = fopen("saida_mst.txt", "w");
    if (outputFile == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    // Encontre a árvore geradora mínima usando o algoritmo de Kruskal
    for (int i = 0; i < edgeCount; i++) {
        int city1 = edges[i].city1;
        int city2 = edges[i].city2;
        int root1 = find(set, city1);
        int root2 = find(set, city2);

        // Verifique se adicionar esta aresta não criará um ciclo
        if (root1 != root2) {
            fprintf(outputFile, "Aresta entre Cidade %d e Cidade %d: dist=%.2lf\n", city1, city2, edges[i].distance);
            totalCost += edges[i].distance;
            unionSets(set, root1, root2);
            edgesInTree++;

            // Se todas as cidades estiverem na árvore, pare
            if (edgesInTree == dimension - 1) {
                break;
            }
        }
    }

    // Escreva o custo total da árvore geradora mínima no arquivo de saída
    fprintf(outputFile, "\nCusto total da Árvore Geradora Mínima: %.2lf\n", totalCost);

    fclose(file);
    fclose(outputFile);

    printf("Arquivo de saída 'saida_mst.txt' gerado com sucesso.\n");
    
    // Libere a memória alocada para o conjunto disjunto
    free(set->parent);
    free(set);

    return 0;
}
