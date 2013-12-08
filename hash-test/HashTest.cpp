#include "Snap.h"

int main() {
    //TPHash<TPair<TIntV, TFltV>, TInt >T;
    //TIntV A; A.Add(1); A.Add(2);
    //TFltV B; B.Add(1); A.Add(2.5);

    //T.Gen(10);
    //T.AddDat(TPair<TIntV, TFltV>(A, B), 3); 

    //printf("%d\n", T.Len());
    srand(time(0));
    TPHash<TInt, TInt> T;
    
    T.Clr();
    T.Gen(100005);
    
    #pragma omp parallel for num_threads(100)
    for (int i = 1; i <= 100000; i++) {
      T.AddDat(rand()%100, rand()%100);
    }
    
    TInt sum = 0;
    for (TPHash<TInt, TInt>::TIter it = T.BegI(); it != T.EndI(); it++) {
      printf("%d\n", it.GetKey().Val);
      sum += 1;
      //TPair<TInt, TIntV> V = it.GetDat();
    
      //printf("%d\n", it.GetKey().Val);
      //sum += V.Val2.Len();
      ////for (TInt i = 0; i < V.Val2.Len(); i++)
      //  printf("%d ", V.Val2[i].Val);
      //printf("\n");
    }
    printf("Total number of elements inserted: %d\n", sum.Val);
    
    //THashPar<TInt, TInt> Q;
    //Q.ResizePar(1005);
    
    //#pragma omp parallel for num_threads(100)
    //for (int i = 1; i <= 1000000; i++) {
    //  Q.AddKeyPar(rand()%100);
    //}
    
    //int s = 0;
    //for (THashPar<TInt, TInt>::TIter it = Q.BegI(); it != Q.EndI(); it++) {
    //  printf("%d\n", it.GetKey().Val);
    //  s += 1;
    //  //for (QInt i = 0; i < V.Val2.Len(); i++)
    //  //  printf("%d ", V.Val2[i].Val);
    //  //printf("\n");
    //}
    //printf("Total number of keys added: %d\n", s);

  
  return 0;
}
