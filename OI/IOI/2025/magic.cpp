#include "magic.h"
#include<bits/stdc++.h>
using namespace std;


std::vector<int> Alicia(std::vector<int> P) {
  int N=(int)P.size();
  vector<int> is(N,1),ds(N,1);

  int lis=0,lds=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<i;j++) if(P[j]<P[i]) is[i]=max(is[i],is[j]+1);
    lis=max(lis,is[i]);
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<i;j++) if(P[j]>P[i]) ds[i]=max(ds[i],ds[j]+1);
    lds=max(lds,ds[i]);
  }
  assert(lis*lds>=N);
  if(lis>=16){
    int X=N+1;lis=16;
    for(int i=N-1;i>=0;i--){
      if(is[i]==lis && P[i]<X) X=P[i],P[i]=-1,lis--;
    }
  }
  else{
    int X=-1;lds=17;
    for(int i=N-1;i>=0;i--){
      if(ds[i]==lds && P[i]>X) X=P[i],P[i]=-1,lds--;
    }
  }
  return P;
}

std::vector<int> Beatriz(std::vector<int> Q) {
  int N=(int)Q.size();

  int k=0;
  vector<bool> ins(N+1);
  for(int i=0;i<N;i++){
    if(Q[i]!=-1) ins[Q[i]]=true;
    else k++;
  }
  vector<int> val;
  for(int i=1;i<=N;i++) if(!ins[i]) val.push_back(i);
  if(!(k&1)) reverse(val.begin(),val.end());
  for(int i=0;i<N;i++) if(Q[i]==-1) Q[i]=val.back(),val.pop_back();
  return Q;
}