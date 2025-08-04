#include "worldmap.h"
#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> create_map(int N, int M, vector<int> A, vector<int> B) {
  vector<vector<int>> g(N),child(N);
  for(int i=0;i<M;i++) A[i]--,B[i]--,g[A[i]].push_back(B[i]),g[B[i]].push_back(A[i]);
  
  int T=0,X=0;
  vector<int> f(N),d(N),par(N);
  function<void(int)> dfs = [&](int u){
    f[u]=++T;
    if(d[u]>d[X]) X=u;
    for(int v:g[u]) if(!f[v]){
      par[v]=u,d[v]=d[u]+1,dfs(v);
      child[u].push_back(v);
    }
  };
  dfs(0);

  vector<bool> path(N),vis(N);
  while(X) path[X]=true,X=par[X];

  int S=2*N;
  vector<vector<int>> ans(S,vector<int>(S,0));

  int k=0,lst=-1;
  auto add = [&](int x){
    for(int i=max(0,k-S+1);i<min(k+1,S);i++) ans[i][k-i]=x+1;
    k++;lst=x;
  };
  function<void(int)> build = [&](int u){
    add(u);add(u);k--;
    int i=max(0,k-S+1);
    for(int v:g[u]) if(f[v]<f[u] && v!=par[u]){
      ans[i][k-i]=v+1,i++;
    }
    k++;
    add(u);

    int nxt=0;
    for(int v:child[u]){
      if(path[v]) nxt=v;
      else{
        build(v);
        add(u);
      }
    }
    if(nxt){
      build(nxt);
      add(u);
    }
  };
  build(0);
  while(k<2*S) add(lst);
  return ans;
}
