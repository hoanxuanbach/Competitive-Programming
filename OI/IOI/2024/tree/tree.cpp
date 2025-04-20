#include "tree.h"
#include<bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
const int maxn = 2e5+5;
const int inf = 1e6;

vector<pair<int,int>> val,sum;
int n,p[maxn],w[maxn],total;
vector<int> edge[maxn];

int par[maxn],d[maxn],pos[maxn];
void init(std::vector<i32> P, std::vector<i32> W) {
  n = (int)P.size();
  vector<pair<int,int>> X;
  for(int i=0;i<n;i++){
    p[i]=P[i],w[i]=W[i];
    X.push_back({w[i],i});
  }
  for(int i=1;i<n;i++){
    d[p[i]]++;
    edge[p[i]].push_back(i);
    edge[i].push_back(p[i]);
  }
  for(int i=0;i<n;i++) if(!d[i]) d[i]++,total+=w[i];
  sort(X.begin(),X.end());
  memset(par,-1,sizeof(par));
  function<int(int)> findpar = [&](int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
  };
  while(!X.empty()){
    auto [x,u]=X.back();X.pop_back();
    par[u]=u;
    for(int v:edge[u]) if(par[v]!=-1){
      v=findpar(v);par[v]=u;d[u]+=d[v]-1;
      val.push_back({d[v],(pos[v]-x)});
    }
    pos[u]=x;
  }
  int u=findpar(1);
  val.push_back({d[u],pos[u]});
  sort(val.begin(),val.end());
  for(int i=0;i<(int)val.size();i++){
    auto [x,y]=val[i];
    sum.push_back({y,x*y});
  }
  for(int i=(int)sum.size()-2;i>=0;i--){
    sum[i].first+=sum[i+1].first;
    sum[i].second+=sum[i+1].second;
  }
}

int query(i32 _L, i32 _R) {
  int L=_L,R=_R;
  int x=upper_bound(val.begin(),val.end(),make_pair(R/L,inf))-val.begin();
  int res=L*total;
  if(x<(int)val.size()) res+=L*sum[x].second-R*sum[x].first;
  return res;
}
