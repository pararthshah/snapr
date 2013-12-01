#include "time.h"

#include "Snap.h"

int main(){
  TTableContext Context;
  // create scheme
  Schema AnimalS;
  AnimalS.Add(TPair<TStr,TAttrType>("Animal", atStr));
  AnimalS.Add(TPair<TStr,TAttrType>("Size", atStr));
  AnimalS.Add(TPair<TStr,TAttrType>("Location", atStr));
  AnimalS.Add(TPair<TStr,TAttrType>("Number", atInt));
  TIntV RelevantCols;
  RelevantCols.Add(0);
  RelevantCols.Add(1);
  RelevantCols.Add(2);
  RelevantCols.Add(3);

  PTable P = TTable::LoadSS("Animals", AnimalS, "tests/t.txt", Context, RelevantCols);

  P->SaveSS("tests/p1.txt");

  TStrV cols;
  cols.Add("Size");
  cols.Add("Number");

  struct timeval begin, end;
  gettimeofday(&begin, NULL);

  P->Unique(cols);
  //P->Group(cols, "SizeNumberGroup");

  gettimeofday(&end, NULL);

  double diff = (end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec);
  printf("Elapsed time:%.3lfs\n", diff / 1000000);

  P->SaveSS("tests/p3.txt");

  return 0;
}
