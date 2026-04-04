#include "multi.h"
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
const ull inf = 1e18;

struct dsu{
  int n;
  vector<int> f;
  dsu(int _n = 0):n(_n){
    f.assign(n,0);
    iota(f.begin(),f.end(),0);
  }
  void clear(){
    iota(f.begin(),f.end(),0);
  }
  int ff(int u){
    if(f[u]!=u) return f[u]=ff(f[u]);
    return u;
  }
  bool unite(int u,int v){
    u=ff(u);v=ff(v);
    if(u!=v){
      f[v]=u;
      return true;
    }
    return false;
  }
};

std::vector<ull> strategy(int N, int r, int x,
                                         std::vector<ull> A,
                                         std::vector<ull> B) {
  
  if(r==0){
    vector<pair<ull,int>> P;
    for(int i=0;i<N;i++) if(x!=i) P.push_back({A[i],i});
    sort(P.begin(),P.end());
    P.push_back({0,x});

    ull val=P[0].second+P[1].second*N+P[1].first*N*N;
    vector<ull> ret(N,val);
    return ret;
  }

  auto get_par = [&](vector<pair<int,int>> E){
    vector<vector<int>> g(N);
    for(auto [u,v]:E){
      g[u].push_back(v);
      g[v].push_back(u);
    }
    vector<int> p(N);
    vector<bool> vis(N);

    function<void(int)> dfs = [&](int u){
      vis[u]=true;
      for(int v:g[u]) if(!vis[v]){
        p[v]=u;
        dfs(v);
      }
    };

    for(int i=0;i<N;i++) if(!vis[i]) p[i]=i,dfs(i);
    return p;
  };

  auto get_f = [&](vector<int> par){
    int cnt=0;
    vector<int> f(N);

    dsu T(N);
    for(int i=0;i<N;i++) T.unite(i,par[i]);
    for(int i=0;i<N;i++) if(T.ff(i)==i) f[i]=cnt++;
    for(int i=0;i<N;i++) if(T.ff(i)!=i) f[i]=f[T.ff(i)];

    return make_pair(cnt,f);
  };

  if(r>=1 && r<=3){
    dsu T(N);
    vector<pair<int,int>> E;
    for(int u=0;u<N;u++){
      int v=B[u]%N;
      if(T.unite(u,v)) E.push_back({u,v});
    }

    vector<vector<int>> g(N);
    for(int u=0;u<N;u++) g[T.ff(u)].push_back(u);

    vector<pair<ull,pair<int,int>>> S;
    for(int i=0;i<N;i++) if(g[i].size()){
      pair<ull,pair<int,int>> X={inf,{-1,-1}};
      for(int u:g[i]){
        B[u]/=N;
        int v=B[u]%N;
        ull w=B[u]/N;
        X=min(X,{w,{u,v}});
      }
      S.push_back(X);
    }
  
    sort(S.begin(),S.end());
    for(auto [w,e]:S){
      auto [u,v]=e;
      if(T.unite(u,v)) E.push_back({u,v});
    }

    vector<int> par=get_par(E);

    if(r<=2){
      vector<pair<ull,int>> P;
      for(int i=0;i<N;i++) if(T.ff(x)!=T.ff(i)) P.push_back({A[i],i});
      sort(P.begin(),P.end());
      P.push_back({0,x});

      ull val=par[x]+P[0].second*N+P[0].first*N*N;
      vector<ull> ret(N,val);
      return ret;
    }
    else{
      auto [cnt,f]=get_f(par);

      vector<ull> K(cnt,1ULL<<48);
      for(int i=0;i<N;i++) K[f[i]]=min(K[f[i]],A[i]);
      
      vector<ull> ret(N,par[x]);
      ret[0]+=A[par[x]]*N;

      int cur=1;
      for(int i=0;i<cnt;i++) for(int j=i+1;j<cnt;j++){
        if(f[x]==i) ret[cur]+=K[j]*N;
        cur++;
      }

      return ret;
    }
  }
  if(r==4){
    vector<int> par(N);
    for(int i=0;i<N;i++) par[i]=B[i]%N;

    if(x==0){
      ull mst=0;
      for(int i=1;i<N;i++) mst+=B[i]/N;
      vector<ull> ret(N,mst*N);
      return ret;
    }
    else{
      vector<ull> ret(N,par[x]);
      auto [cnt,f]=get_f(par);
      
      if(x>cnt*(cnt-1)/2) return ret;

      int cur=1;
      for(int i=0;i<cnt;i++) for(int j=i+1;j<cnt;j++){
        if(cur==x){
          ull W=(1ULL<<48);
          for(int u=0;u<N;u++) if(f[u]==i) W=min(W,B[u]/N);
          ret[0]+=W*N;
        }
        cur++;
      }
      return ret;
    }
    
  }
  if(r==5){
    if(x!=0) return B;
    ull mst=B[0]/N;

    vector<int> par(N);
    for(int i=0;i<N;i++) par[i]=B[i]%N;
    auto [cnt,f]=get_f(par);

    vector<pair<ull,pair<int,int>>> S;
    int cur=1;
    for(int i=0;i<cnt;i++) for(int j=i+1;j<cnt;j++){
      ull W=B[cur]/N;
      S.push_back({W,{i,j}});
      cur++;
    }

    sort(S.begin(),S.end());
    dsu D(cnt);

    for(auto [w,e]:S){
      auto [u,v]=e;
      if(D.unite(u,v)) mst+=w;
    }

    return {mst};
  }

  return {0};
}
