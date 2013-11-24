#include "Snap.h"

int main() {
<<<<<<< HEAD
  srand(time(0));
  THashPar<TInt, TIntV> T;
  T.ResizePar(1000);

  #pragma omp parallel for num_threads(2)
  for (int i = 1; i <= 1000000; i++) {
    T.AddDatPar(rand()%100, rand()%100);
  }

  TInt sum = 0;
  for (THashPar<TInt, TIntV>::TIter it = T.BegI(); it != T.EndI(); it++) {
    TIntV V = it.GetDat();
    //printf("%d: ", it.GetKey().Val);
    sum += V.Len();
    //for (TInt i = 0; i < V.Len(); i++)
    //  printf("%d ", V[i].Val);
    //printf("\n");
  }
  printf("Total number of elements inserted: %d\n", sum);
  return 0;
}
