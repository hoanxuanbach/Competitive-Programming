#include "nile.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5+5;
const int inf = 1e9;
int tree[4*maxn][2],a[maxn];
vector<pair<int,int>> P;
void build(int l,int r,int id){
  if(l==r){
    tree[id][l&1]=P[l].second;
    tree[id][(l&1)^1]=inf;
    return;
  }
  int mid=(l+r)>>1;
  build(l,mid,id<<1);build(mid+1,r,id<<1|1);
  for(int i=0;i<=1;i++) tree[id][i]=min(tree[id<<1][i],tree[id<<1|1][i]);
}
void update(int l,int r,int id,int x){
  if(l==r){
    tree[id][(l&1)^1]=P[l].second;
    return;
  }
  int mid=(l+r)>>1;
  if(x<=mid) update(l,mid,id<<1,x);
  else update(mid+1,r,id<<1|1,x);
  for(int i=0;i<=1;i++) tree[id][i]=min(tree[id<<1][i],tree[id<<1|1][i]);
}
int query(int l,int r,int id,int tl,int tr){
  if(tr<l || r<tl) return inf;
  if(tl<=l && r<=tr) return tree[id][tl&1];
  int mid=(l+r)>>1;
  return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
}

std::vector<ll> calculate_costs(std::vector<int> W, std::vector<int> A,
                                       std::vector<int> B, std::vector<int> E) {
  int N=(int)A.size(),Q=(int)E.size();
  vector<ll> res(Q);

  ll total=0;
  for(int i=0;i<N;i++) total+=A[i],P.push_back({W[i],A[i]-B[i]});
  sort(P.begin(),P.end());

  build(0,N-1,1);
  auto get = [&](int l,int r){
    if((r-l)&1) return 0;
    return query(0,N-1,1,l,r);
  };
  
  vector<int> p(N),l(N),r(N);
  for(int i=0;i<N;i++) p[i]=l[i]=r[i]=i;
  function<int(int)> findpar = [&](int u){
    if(p[u]!=u) return p[u]=findpar(p[u]);
    return u;
  };
  auto change = [&](int x){
    if(x<0){
      x=-x;
      int u=findpar(x-1),v=findpar(x);
      total-=get(l[u],r[u])+get(l[v],r[v]);
      p[v]=u;r[u]=r[v];
      total+=get(l[u],r[u]);
    }
    else{
      int u=findpar(x);
      total-=get(l[u],r[u]);
      update(0,N-1,1,x);
      total+=get(l[u],r[u]);
    }
  };
  
  
  vector<pair<int,int>> X;
  for(int i=1;i<N;i++) X.push_back({P[i].first-P[i-1].first,-i});
  for(int i=1;i<N-1;i++) X.push_back({P[i+1].first-P[i-1].first,i});
  sort(X.begin(),X.end());

  vector<pair<int,int>> qq;
  for(int i=0;i<Q;i++) qq.push_back({E[i],i});
  sort(qq.begin(),qq.end());
  
  int pos=0;
  for(auto [D,id]:qq){
    while(pos<(int)X.size() && X[pos].first<=D) change(X[pos++].second);
    res[id]=total;
  }
  return res;
}
