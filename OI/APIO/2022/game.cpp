#include "game.h"
#include<bits/stdc++.h>
using namespace std;

const int maxn = 3e5+5;
int n,k,f,l[maxn],r[maxn],cc[maxn];
vector<int> edge[maxn],rev_edge[maxn];

void init(int N, int K) {
    n=N;k=K;
    for(int i=0;i<k;i++) l[i]=i,r[i]=i+1;
    for(int i=k;i<n;i++) l[i]=0,r[i]=k+1;
    for(int i=0;i<n;i++) cc[i]=__lg(l[i]^r[i]);
}

void update(int u){
    if(f) return;
    if(r[u]<=l[u]) return void(f=1);
    int nw=__lg(l[u]^r[u]);
    if(nw==cc[u]) return;
    cc[u]=nw;
    for(int v:edge[u]){
        if(l[v]<l[u]) l[v]=l[u],update(v);
    }
    for(int v:rev_edge[u]){
        if(r[v]>r[u]) r[v]=r[u],update(v);
    }
}

int add_teleporter(int u, int v) {
    if(v<=u && u<k) return 1;
    if(u==v) return 0;
    edge[u].push_back(v);
    rev_edge[v].push_back(u);
    int x=(u<k?max(u+1,l[u]):l[u]);
    if(l[v]<x) l[v]=x,update(v);
    if(r[u]>r[v]) r[u]=r[v],update(u);
    return f;
}
