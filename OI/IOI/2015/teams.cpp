#include "teams.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
const int maxl = 25;
const int inf = 1e9;

int n;
int tree[maxn*maxl],lc[maxn*maxl],rc[maxn*maxl],T=1;
void build(int l,int r,int id){
    if(l==r) return;
    lc[id]=++T;rc[id]=++T;
    int mid=(l+r)>>1;
    build(l,mid,lc[id]);build(mid+1,r,rc[id]);
}
int update(int l,int r,int id,int p){
    if(l==r){
        tree[++T]=tree[id]+1;
        return T;
    }
    int mid=(l+r)>>1;
    int cc=++T;
    lc[cc]=lc[id];rc[cc]=rc[id];
    if(p<=mid) lc[cc]=update(l,mid,lc[id],p);
    else rc[cc]=update(mid+1,r,rc[id],p);
    tree[cc]=tree[lc[cc]]+tree[rc[cc]];
    return cc;
}
int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return 0;
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    return query(l,mid,lc[id],tl,tr)+query(mid+1,r,rc[id],tl,tr);
}
vector<int> e[maxn];
int root[maxn];

void init(int N, int A[], int B[]) {
    for(int i=0;i<N;i++) e[B[i]].push_back(A[i]);
    n=N;
    root[N+1]=1;
    build(1,N,1);
    for(int i=N;i>=1;i--){
        root[i]=root[i+1];
        for(int x:e[i]) root[i]=update(1,n,root[i],x);
    }
}

int cnt[maxn],dp[maxn];

int can(int M, int K[]) {
    vector<int> C;
    for(int i=0;i<M;i++){
        if(!cnt[K[i]]) C.push_back(K[i]);
        cnt[K[i]]+=K[i];
    }
    auto get = [&](int l,int r){
        l=(l==-1?0:C[l]);
        r=(r==-1?0:C[r]);
        return dp[l]+query(1,n,root[r],l+1,r)-cnt[r];
    };
    sort(C.begin(),C.end());
    vector<pair<int,int>> p;
    p.push_back({0,-1});
    int sz=(int)C.size();

    for(int i=0;i<sz;i++){
        /*
        int k=upper_bound(p.begin(),p.end(),make_pair(i,inf))-p.begin()-1;
        dp[C[i]]=get(p[k].second,i);
        if(dp[C[i]]<0){
            for(int x:C) cnt[x]=dp[x]=0;
            return 0;
        }
        while(!p.empty()){
            auto [x,j]=p.back();
            if(i<x && get(j,x)>=get(i,x)) p.pop_back();
            else break;
        }
        auto [l,j]=p.back();
        int r=sz;l++;
        while(l<r){
            int mid=(l+r)>>1;
            if(i<mid && get(j,mid)<=get(i,mid)) r=mid;
            else l=mid+1;
        }
        if(r<sz) p.push_back({r,i});
        */
        int x=C[i];
        dp[x]=inf;
        for(int j=max(-1,i-10);j<i;j++) dp[x]=min(dp[x],get(j,i));
        if(dp[x]<0){
            for(int x:C) cnt[x]=dp[x]=0;
            return 0;
        }
    }
    for(int x:C) cnt[x]=dp[x]=0;
    return 1;
}
