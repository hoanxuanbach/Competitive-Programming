#include "towns.h"
#include<bits/stdc++.h>
using namespace std;

int find_town(int N) {

  vector<int> deg(N);
  vector<vector<int>> G(N,vector<int>(N,-1));

  auto f = [&](int u,int v){
    if(G[u][v]!=-1) return G[u][v];
    G[u][v]=check_road(u,v);
    G[v][u]=G[u][v]^1;
    if(G[u][v]) deg[u]++;
    else deg[v]++;
    return G[u][v];
  };

  int X=0;
  for(int i=1;i<N;i++) if(f(X,i)) X=i;
  vector<int> S;
  for(int i=0;i<N;i++){
    if(i==X) continue;
    if(deg[X]>1 || G[X][i]!=-1){
      S.push_back(i);
      continue;
    }
    if(f(X,i)) S.push_back(i);
  }
  if(deg[X]<=1) return X;
  while((int)S.size()>2){
    bool found=false;
    int sz=(int)S.size();
    for(int i=0;i<sz;i++){
      if(found) break;
      for(int j=0;j<i;j++){
        int u=S[i],v=S[j];
        if(G[u][v]!=-1) continue;
        found = true;
        if(f(u,v)) S[i]=S.back();
        else S[j]=S.back();
        S.pop_back();
        break;
      }
    }
  }
  for(int x:S){
    for(int i=0;i<N;i++) if(x!=i) f(x,i);
    if(deg[x]<=1) return x;
  }
  return -1;
}
