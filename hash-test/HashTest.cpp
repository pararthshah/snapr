#include "Snap.h"

int main() {
  THashPar<TInt, TInt> T;
  T.ResizePar(1000);

  #pragma omp parallel for num_threads(1)
  for (int i = 1; i <= 1000; i++) {
    //printf("%d\n", i);
    for (int j = 1; j <= 10000; j++) {
      T.AddDatPar(rand()%10, rand()%100);
    }
  }

  for (THash<TInt, TInt>::TIter it = T.BegI(); it != T.EndI(); it++) {
    printf("%d %d\n", it.GetKey().Val, it.GetDat().Val);
  }
  return 0;
}
