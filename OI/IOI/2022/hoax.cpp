#include "hoax.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> res;
void init(int N, int S, std::vector<int> T,
          std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
  
  res.assign(N,0);
  vector<int> P={0,S+1};
  for(int i=0;i<N;i++) for(int j=0;j<T[i];j++){
    B[i][j]++;
    P.push_back(A[i][j]);
    P.push_back(B[i][j]);
  }
  sort(P.begin(),P.end());
  P.erase(unique(P.begin(),P.end()),P.end());
  S=(int)P.size()-1;

  vector<int> add(S+1),del(S+1);
  for(int i=0;i<N;i++) for(int j=0;j<T[i];j++){
    A[i][j]=lower_bound(P.begin(),P.end(),A[i][j])-P.begin();
    B[i][j]=lower_bound(P.begin(),P.end(),B[i][j])-P.begin();
    add[A[i][j]]++;del[B[i][j]]++;
  }
  
  vector<int> pos;
  {
    int cur=0;
    for(int i=0;i<S;i++){
      if(!cur) pos.push_back(i);
      cur+=add[i]-del[i+1];
    }
    pos.push_back(S);
  }

  vector<int> par(N),sz(N,1);
  iota(par.begin(),par.end(),0);

  function<int(int)> findpar = [&](int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
  };
  auto unions = [&](int u,int v){
    u=findpar(u);v=findpar(v);
    if(u!=v) par[v]=u,sz[u]+=sz[v];
  };

  S=(int)pos.size();
  vector<int> lst(S,-1);
  for(int i=0;i<N;i++) for(int j=0;j<T[i];j++){
    int id=upper_bound(pos.begin(),pos.end(),A[i][j])-pos.begin()-1;
    if(lst[id]!=-1) unions(lst[id],i);
    lst[id]=i;
  }
  for(int i=0;i<N;i++) res[i]=sz[findpar(i)];
}

int count_users(int P) {
  return res[P];
}
