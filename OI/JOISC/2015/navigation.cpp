#include "navigation_lib.h"
#include<bits/stdc++.h>
using namespace std;

void Anna(int K, int N, int T, int A[], int B[]) {
    vector<vector<int>> edge(N+1);
    for(int i=0;i<N-1;i++){
        edge[A[i]].push_back(B[i]);
        edge[B[i]].push_back(A[i]);
    }
    function<void(int,int,int)> dfs = [&](int u,int p,int t){
        Flag(u,t);
        for(int v:edge[u]) if(v!=p) dfs(v,u,t^(v<u));
    };
    dfs(T,0,0);
}

void Bruno(int K,int S,int F,int L,int P[],int Q[]){
    for(int i=0;i<L;i++) if(F^Q[i]^(P[i]<S)) return Answer(P[i]);
    Answer(S);
}
