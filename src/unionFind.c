void ufInit(int size, int Id[]){
  int N = size;

  // Inicializa o vetor de identificação (Id) de cada elemento com seus próprios índices.
  for (int i = 0; i < N; i++) {
    Id[i] = i;
  }
}

int ufFind(int i, int Id[], int dimension) {
  // Utiliza uma busca para encontrar a raiz do conjunto ao qual i pertence.

  while (i != Id[i]) i = Id[i];
  return i; 
}


void ufUnion(int p, int q, int Id[], int dimension) {
  int i = ufFind(p, Id, dimension);
  int j = ufFind(q, Id, dimension);

  // Define o representante do conjunto de p como o representante do conjunto de q.
  Id[i] = j;
}