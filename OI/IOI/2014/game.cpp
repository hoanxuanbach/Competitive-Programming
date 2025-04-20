#include "game.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1505;

int n,num[maxn][maxn],sz[maxn],par[maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void initialize(int N) {
    n=N;
    for(int i=0;i<n;i++) par[i]=i,sz[i]=1;
}

void unions(int u,int v){
    par[v]=u;sz[u]+=sz[v];
    for(int i=0;i<n;i++){
        num[u][i]+=num[v][i];
        num[i][u]+=num[i][v];
    }
}
int hasEdge(int u, int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return 0;
    else{
        if(num[u][v]==sz[u]*sz[v]-1) return unions(u,v),1;
        num[u][v]++;num[v][u]++;
        return 0;
    }
}
