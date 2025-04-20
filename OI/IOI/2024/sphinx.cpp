#include "sphinx.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 255;
vector<int> edge[maxn],edge2[maxn];
int N,vis[maxn],T;
bool adj[maxn];

int query(vector<int> E){
  int cnt=perform_experiment(E);
  vector<bool> cc(N,false);
  function<void(int)> dfs = [&](int u){
    cc[u]=true;
    for(int v:edge[u]) if(!cc[v] && E[v]==E[u]) dfs(v);
  };
  for(int i=0;i<N;i++) if(!cc[i] && E[i]!=-1) cnt--,dfs(i);
  return cnt;
}

vector<vector<int>> dfs(int u,int p){
  vis[u]=++T;
  vector<vector<int>> A;

  vector<int> child;
  for(int v:edge[u]){
    if(!vis[v]){
      vector<vector<int>> B=dfs(v,u);
      A.insert(A.end(),B.begin(),B.end());
    }
    if(vis[v]>vis[u]) adj[v]=true,child.push_back(v);
  }
  vector<vector<int>> X,Y;
  for(auto cur:A){
    bool add=false;
    for(int v:cur) if(adj[v]) add=true;
    if(add) X.push_back(cur);
    else Y.push_back(cur);
  }

  vector<int> nw;
  nw.push_back(u);
  while(!X.empty()){
    vector<int> E(N,N);
    
    E[u]=-1;
    for(auto cur:X) for(int v:cur) E[v]=-1;
    if(query(E)==(int)X.size()+1) break;
    int l=0,r=(int)X.size()-1;
    while(l<r){
      int m=(l+r)>>1;
      E.assign(N,N);E[u]=-1;
      for(int i=0;i<=m;i++) for(int v:X[i]) E[v]=-1;
      if(query(E)==m+2) l=m+1;
      else r=m;
    }
    for(int i=0;i<l;i++){
      Y.push_back(X[0]);
      X.erase(X.begin());
    }
    nw.insert(nw.end(),X[0].begin(),X[0].end());
    X.erase(X.begin());
  }
  for(auto cur:X) Y.push_back(cur);
  Y.push_back(nw);
  for(int v:child) adj[v]=false;
  return Y;
};

std::vector<int> find_colours(int _N, std::vector<int> X, std::vector<int> Y) {
  N=_N;T=0;
  for(int i=0;i<N;i++) edge[i].clear(),vis[i]=adj[i]=0;
  for(int i=0;i<(int)X.size();i++){
    edge[X[i]].push_back(Y[i]);
    edge[Y[i]].push_back(X[i]);
  }
  vector<vector<int>> A=dfs(0,-1);
  vector<int> C(N),f(N);
  int S=(int)A.size();
  for(int i=0;i<S;i++){
    for(int u:A[i]) f[u]=i;
  }
  for(int i=0;i<(int)X.size();i++){
    X[i]=f[X[i]];Y[i]=f[Y[i]];
    if(X[i]!=Y[i]){
      edge2[X[i]].push_back(Y[i]);
      edge2[Y[i]].push_back(X[i]);
    }
  }
  for(int i=0;i<S;i++){
    vis[i]=0;
    sort(edge2[i].begin(),edge2[i].end());
    edge2[i].erase(unique(edge2[i].begin(),edge2[i].end()),edge2[i].end());
  }

  vector<int> D(S);
  if(S==1){
    for(int i=0;i<N;i++){
      vector<int> E(N,i);E[0]=-1;
      if(perform_experiment(E)==1){
        D[0]=i;
        break;
      }
    }
  }
  else{
    vector<vector<int>> P(2),K(2);
    function<void(int,int)> dfs2 = [&](int u,int d){
      P[d].push_back(u);vis[u]=1;
      for(int v:edge2[u]) if(!vis[v]) dfs2(v,d^1);
    };
    dfs2(0,0);
    K=P;
    for(int i=0;i<N;i++){
      for(int k=0;k<=1;k++){
        vector<int> B=P[k];
        while(!B.empty()){
          auto check = [&](int m){
            vector<int> E(N,N);
            for(int x:K[k^1]) for(int v:A[x]) E[v]=i;
            for(int j=0;j<=m;j++) for(int v:A[B[j]]) E[v]=-1;
            return (query(E)!=(m+1));
          };
          int l=0,r=(int)B.size()-1;
          if(!check(r)) break;
          while(l<r){
              int m=(l+r)>>1;
              if(check(m)) r=m;
              else l=m+1;
          }
          D[B[l]]=i;
          P[k].erase(find(P[k].begin(),P[k].end(),B[l]));
          B.erase(B.begin(),B.begin()+l+1);
        }
      }
    }
  }
  for(int i=0;i<S;i++) for(int v:A[i]) C[v]=D[i];
  return C;
}
