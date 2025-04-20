#include "swap.h"
#include <bits/stdc++.h>
using namespace std;
const int inf = 2e9;
const int maxn = 2e5+5;
int a[maxn],c[maxn],d[maxn],p[maxn];

int findpar(int u){
    return (p[u]<0?u:findpar(p[u]));
}
void unions(int u,int v,int w,bool e){
    u=findpar(u);v=findpar(v);
    if(u==v) c[u]=min(c[u],w);
    else{
        if(p[u]>p[v]) swap(u,v);
        p[u]+=p[v];p[v]=u;a[v]=w;
        c[u]=min(c[u],max(w,e?0:c[v]));
    }
}

void init(int N, int M,
          std::vector<int> U, std::vector<int> V, std::vector<int> W) {
    for(int i=0;i<N;i++) p[i]=-1,a[i]=c[i]=inf;
    vector<int> ord(M);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return W[x]<W[y];
    });
    for(int i:ord){
        d[U[i]]++;d[V[i]]++;
        unions(U[i],V[i],W[i],(d[U[i]]>=3 || d[V[i]]>=3));
    }
}

int getMinimumFuelCapacity(int u, int v) {
    int w=-1;
    while(u!=v){
        if(a[u]<a[v]) w=a[u],u=p[u];
        else w=a[v],v=p[v];
    }
    while(u>=0){
        if(c[u]!=inf) return max(w,c[u]);
        w=a[u];u=p[u];
    }
    return -1;
}
