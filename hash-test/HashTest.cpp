#include "Snap.h"

int main() {
  srand(time(0));
  THashPar<TInt, TPair<TInt, TIntV> > T;
  T.ResizePar(1000005);

  #pragma omp parallel for num_threads(100)
  for (int i = 1; i <= 1000000; i++) {
    T.AddDatPar(rand()%100, rand()%100);
  }

  TInt sum = 0;
  for (THashPar<TInt, TPair<TInt, TIntV> >::TIter it = T.BegI(); it != T.EndI(); it++) {
    TPair<TInt, TIntV> V = it.GetDat();
    printf("%d\n", it.GetKey().Val);
    sum += V.Val2.Len();
    //for (TInt i = 0; i < V.Val2.Len(); i++)
    //  printf("%d ", V.Val2[i].Val);
    //printf("\n");
  }
  printf("Total number of elements inserted: %d\n", sum.Val);

  THashPar<TInt, TInt> Q;
  Q.ResizePar(1005);

  #pragma omp parallel for num_threads(100)
  for (int i = 1; i <= 1000000; i++) {
    Q.AddKeyPar(rand()%100);
  }

  int s = 0;
  for (THashPar<TInt, TInt>::TIter it = Q.BegI(); it != Q.EndI(); it++) {
    printf("%d\n", it.GetKey().Val);
    s += 1;
    //for (QInt i = 0; i < V.Val2.Len(); i++)
    //  printf("%d ", V.Val2[i].Val);
    //printf("\n");
  }
  printf("Total number of keys added: %d\n", s);

  
  return 0;
}
