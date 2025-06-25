#include "lottery.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int maxn = 2e5+5;
const int maxa = 2e9;

struct DS{
  struct node{
    ll sum=0;
    int cnt=0;
    node *cl=nullptr,*cr=nullptr;
  };

  int sz=0;
  node* root[maxn];

  DS(){
    root[0]=new node();
  }
  node *get_cl(node *p){
    if(p) return p->cl;
    else return nullptr;
  }
  node *get_cr(node *p){
    if(p) return p->cr;
    else return nullptr;
  }
  int get_cnt(node *p){
    if(p) return p->cnt;
    else return 0;
  }
  ll get_sum(node *p){
    if(p) return p->sum;
    else return 0;
  }

  node* update(int l,int r,node *p,int x){
    node *cur = new node();
    if(p) *cur = *p;
    cur->cnt++;
    cur->sum+=x;
    if(l==r) return cur;
    int mid=l+(r-l)/2;
    if(x<=mid) cur->cl=update(l,mid,get_cl(p),x);
    else cur->cr=update(mid+1,r,get_cr(p),x);
    return cur;
  };

  void add(int x){
    root[sz+1]=update(0,maxa,root[sz],x);
    sz++;
  }
  int query(int l,int r,node *px,node *py,ll csum,int ccnt,int ss){
    if(l==r) return l;
    int mid=l+(r-l)/2;
    ll nsum = get_sum(get_cl(py))-get_sum(get_cl(px));
    int ncnt = get_cnt(get_cl(py))-get_cnt(get_cl(px));
    ll val = csum + nsum + 1LL*(mid+1)*(ccnt-ncnt);

    if(val>=1LL*(mid+1)*ss/2) return query(mid+1,r,get_cr(px),get_cr(py),csum+nsum,ccnt-ncnt,ss);
    else return query(l,mid,get_cl(px),get_cl(py),csum,ccnt,ss);
  }
  int get(int l,int r){
    return query(0,maxa,root[l],root[r],0,r-l,r-l);
  }

}sX,sY;

struct Sparse_Table{
  int n;
  vector<vector<int>> val;
  void build(int N,vector<int> X){
    n=N;
    val.assign(20,X);
    for(int i=1;i<20;i++) for(int j=0;j<N;j++) if((j+(1<<(i-1)))<N) val[i][j]=min(val[i-1][j],val[i-1][j+(1<<(i-1))]);
  }
  int get(int l,int r){
    int k=31-__builtin_clz(r-l);
    //assert((1<<k)<=(r-l) && (1<<(k+1))>(r-l));
    return min(val[k][l],val[k][r-(1<<k)]);
  }
}T;

void init(int N, int Q, std::vector<int> X, std::vector<int> Y) {
  for(int i=0;i<N;i++) sX.add(X[i]);
  for(int i=0;i<N;i++) sY.add(Y[i]),X[i]+=Y[i];
  T.build(N,X);
}

int max_prize(int l, int r) {
  r++;
  return min({T.get(l,r),sX.get(l,r),sY.get(l,r)});
}
