void ufInit(int size, int Id[]){
  int N = size;
  for (int i = 0; i < N; i++) {
    Id[i] = i;
  }
}

int ufFind(int i, int Id[], int dimension) {
  while (i != Id[i]) i = Id[i];
  return i; 
}


void ufUnion(int p, int q, int Id[], int dimension) {
  int i = ufFind(p, Id, dimension);
  int j = ufFind(q, Id, dimension);
  Id[i] = j;
}