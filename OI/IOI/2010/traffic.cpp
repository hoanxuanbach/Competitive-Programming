#include "traffic.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;

int T;
int x,Min;
vector<int> edge[maxn];

int LocateCentre(int N, int pp[], int S[], int D[]) {
    for(int i=0;i<N;i++) T+=pp[i];
    for(int i=0;i<N-1;i++){
        edge[S[i]].push_back(D[i]);
        edge[D[i]].push_back(S[i]);
    }
    function<void(int,int)> dfs = [&](int u,int p){
        int Max=0;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);
            pp[u]+=pp[v];
            Max=max(Max,pp[v]);
        }
        Max=max(Max,T-pp[u]);
        if(Max<Min) Min=Max,x=u;
    };
    Min=T;
    dfs(0,0);
    return x;
}
