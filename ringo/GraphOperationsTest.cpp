#include "Snap.h"
#include <cstring>
#include <ctime>

int main(int argc, char** argv){
  TTableContext Context;
  // create scheme
  Schema StackOverflowS;
  StackOverflowS.Add(TPair<TStr,TAttrType>("Id", atInt));
  StackOverflowS.Add(TPair<TStr,TAttrType>("Parent", atInt));
  StackOverflowS.Add(TPair<TStr,TAttrType>("User", atInt));
  StackOverflowS.Add(TPair<TStr,TAttrType>("Score", atInt));
  StackOverflowS.Add(TPair<TStr,TAttrType>("Tags", atStr));
  TIntV RelevantCols;
  RelevantCols.Add(0);
  RelevantCols.Add(1);
  RelevantCols.Add(2);
  RelevantCols.Add(3);
  RelevantCols.Add(4);

  char filename[50] = "tests/SO_posts.small.tsv";
  if (argc >= 2){
    strcpy(filename,argv[1]);
  }

  PTable Q = TTable::LoadSS("posts", StackOverflowS, filename, Context, RelevantCols);
  //PTable R = TTable::LoadSS("questions", StackOverflowS, filename, Context, RelevantCols);
  /*TStrV Cols; Cols.Add("User");
  printf("aggr start\n");
  struct timeval start, end;
  gettimeofday(&start, NULL);
  //PTable P = Q->Join("Parent", R, "Id");
  Q->Aggregate(Cols, aaMean, "Score", "MeanScore");
  gettimeofday(&end, NULL);
  float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
            end.tv_usec - start.tv_usec) / 1.e6;
  printf("time: %f\n", delta);
  //printf("aggr done: %d %d %d\n", Q->GetNumValidRows().Val, R->GetNumValidRows().Val, P->GetNumValidRows().Val);
  Q->SaveSS("tests/aggr.txt");*/
  TIntV RowIDs;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  Q->SelectAtomicIntConst("Score", 100, LTE, RowIDs, false);
  PTable R = TTable::New(Q, "Select", RowIDs);
  gettimeofday(&end, NULL);
  float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
            end.tv_usec - start.tv_usec) / 1.e6;
  printf("time: %f, R: %d\n", delta, R->GetNumValidRows().Val);
  /*R->SaveSS("tests/select.txt");

  P->SetSrcCol("StackOverflow_1.Id");
  P->SetDstCol("StackOverflow_2.Id");
  //P->AddSrcNodeAttr("StackOverflow_1.Score");
  //P->AddSrcNodeAttr("StackOverflow_2.Score");
  //P->AddEdgeAttr("StackOverflow_1.Tags");
  // THash<TStr, ATTR_AGGR> attrAggr;
  // attrAggr.AddKey("StackOverflow_1.Score");
  // attrAggr.AddDat("StackOverflow_1.Score", FIRST);
  // attrAggr.AddKey("StackOverflow_2.Score");
  // attrAggr.AddDat("StackOverflow_2.Score", FIRST);

  // TVec<PNEANet> NVec = P->ToGraphSequence("StackOverflow_1.Score", attrAggr, 10, 10, TInt::Mn, TInt::Mx);
  TVec<PNEANet> NVec = P->ToGraphSequence("StackOverflow_1.Score", aaFirst, 1000, 1000, TInt::Mn, TInt::Mx);
  printf("vec size: %d\n", NVec.Len());
  TVec<PTable> TableVec;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  TSnap::MapPageRank(NVec, TableVec, Context);
  gettimeofday(&end, NULL);
  float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
            end.tv_usec - start.tv_usec) / 1.e6;
  printf("time: %f\n", delta);
  printf("table size: %d\n", TableVec.Len());
  //for (TNEANet::TNodeI NodeI = N->BegNI(); NodeI < N->EndNI(); NodeI++){
    //printf("%d: <%s>\n", EdgeI.GetId(), N->GetStrAttrDatE(EdgeI, "StackOverflow_1.Tags").CStr());
    //printf("%d %d\n", NodeI.GetId(), N->GetIntAttrDatN(NodeI, "StackOverflow_1.Score").Val);
  //}

  for (TInt i = 0; i < NVec.Len(); i++) {
    printf("graph %d size: %d nodes, %d edges\n", i.Val, NVec[i]->GetNodes(), NVec[i]->GetEdges());
    TableVec[i]->SaveSS("tests/SO_pagerank.txt." + i.GetStr());
  }

  /*PTable NodeTable = TTable::GetNodeTable(N, "NodeTable", Context);
  PTable EdgeTable = TTable::GetEdgeTable(N, "EdgeTable", Context);

  NodeTable->SaveSS("tests/SO_node_table.txt");
  EdgeTable->SaveSS("tests/SO_edge_table.txt");*/
  return 0;
}
