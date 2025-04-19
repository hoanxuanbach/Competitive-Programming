#include "island.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 305;
int d[maxn][maxn];

int Query(int v,int k){
    if(d[v][k]) return d[v][k];
    else return d[v][k]=query(v,k);
}

int dd[maxn],par[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u!=v) par[v]=u;
}

void solve(int N, int L) {
    for(int i=1;i<=N;i++) par[i]=i,dd[i]=1;
    for(int i=1;i<=N;i++){
        for(int u=1;u<=N;u++){
            if(findpar(u)!=findpar(i) && Query(u,dd[u])==i){
                dd[u]++;
                //cout << u << ' ' << i << endl;
                answer(u,i);
                unions(u,i);
            }
        }
    }
}
