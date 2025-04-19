#include "circuit.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int B = 64;

std::string solve(int N, int R, std::vector<int> U, std::vector<int> V) {
  string res(N,'&');

  vector<int> cnt(2*N+1,0);
  function<void(int)> dfs = [&](int x){
    cnt[x]=1;
    if(x>=N) return;
    dfs(U[x]);dfs(V[x]);
    if(cnt[U[x]]<cnt[V[x]]) swap(U[x],V[x]);
    cnt[x]+=cnt[U[x]]+cnt[V[x]];
  };
  dfs(0);

  vector<vector<vector<int>>> g(20);
  function<void(int,int)> dnc = [&](int x,int d){ 
    vector<int> path={x};
    while(x<N) dnc(V[x],d+1),path.push_back({x=U[x]});
    g[d].push_back(path);
  };
  dnc(0,0);

  for(int d=0;!g[d].empty();d++){
    vector<pii> v;
    for(int i=0;i<(int)g[d].size();i++) for(int j=0;j<(int)g[d][i].size()-1;j++) v.push_back({i,j});
    int l=0,sz=(int)v.size();
    
    auto get = [&](int r){
      string s(2*N+1,'0');
      for(int i=N;i<=2*N;i++) s[i]='1';
      auto [x,y]=v[r-1];
      for(int i=0;i<x;i++) s[g[d][i][0]]^=1,s[g[d][i].back()]^=1;
      s[g[d][x][0]]^=1,s[g[d][x][y+1]]^=1;
      for(int i=0;i<N;i++) if(res[i]=='|') s[i]^=1,s[U[i]]^=1,s[V[i]]^=1;
      return query(s)==0;
    };
    while(l<sz){
      int r=min(sz,l+B);
      if(!get(r)){l=r;continue;}
      int lt=l+1,rt=r;
      while(lt<rt){
        int mid=(lt+rt)>>1;
        if(get(mid)) rt=mid;
        else lt=mid+1;
      }
      int x=g[d][v[lt-1].fi][v[lt-1].se];
      res[x]='|';
      l=lt;
    }
  }

  return res;
}
