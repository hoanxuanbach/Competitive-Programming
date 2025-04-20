#include "grader.h"
#include "decoder.h"
#include<bits/stdc++.h>
using namespace std;

void decode(int N, int H) {
    vector<int> par(N),dist(N);
    vector<vector<int>> edge(N);
    vector<vector<int>> dd(H,vector<int>(N,0));
    for(int i=1;i<N;i++){
        for(int j=0;j<10;j++) par[i]+=decode_bit()<<j;
        edge[par[i]].push_back(i);
        edge[i].push_back(par[i]);
        //cout << par[i] << '\n';
    }
    for(int i=0;i<H;i++){
        //cout << '*' << i << '\n';
        for(int j=1;j<N;j+=5){
            int num=0;
            for(int k=0;k<8;k++) num+=decode_bit()<<k;
            for(int u=min(N,j+5)-1;u>=j;u--){
                dist[u]=num%3-1;num/=3;
                //cout << u << ' ' << par[u] <<  ' ' << dist[u] << '\n';
            }
        }
        function<void(int,int)> dfs = [&](int u,int p){
            for(int v:edge[u]){
                if(v==p) continue;
                int w=(par[v]==u?dist[v]:-dist[u]);
                dd[i][v]=dd[i][u]+w;dfs(v,u);
            }
        };
        dd[i][i]=0;
        dfs(i,-1);
        for(int j=0;j<N;j++){
            //cout << "hh " << i << ' ' << j << ' ' << dd[i][j] << '\n';
            hops(i,j,dd[i][j]);
        }
        //cout << '\n';
    }
}
