#include "grader.h"
#include "encoder.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;

void encode(int N, int H, int P, int *A, int *B){
    vector<vector<int>> edge(N);
    vector<int> par(N),dist(N);
    for(int i=0;i<P;i++){
        edge[A[i]].push_back(B[i]);
        edge[B[i]].push_back(A[i]);
    }
    for(int i=0;i<H;i++){
        dist.assign(N,-1);
        queue<int> q;q.push(i);dist[i]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:edge[u]){
                if(dist[v]!=-1) continue;
                q.push(v);dist[v]=dist[u]+1;
                if(!i) par[v]=u;
            }
        }
        if(!i){
            for(int j=1;j<N;j++) for(int k=0;k<10;k++) encode_bit(par[j]>>k&1);
        }
        for(int j=1;j<N;j+=5){
            int num=0;
            for(int u=j;u<min(N,j+5);u++){
                num=num*3+dist[u]-dist[par[u]]+1;
                //cout << i << ' ' << u << ' ' << dist[u]-dist[par[u]] << '\n';
            }
            for(int k=0;k<8;k++) encode_bit(num>>k&1);
        }
    }
}
