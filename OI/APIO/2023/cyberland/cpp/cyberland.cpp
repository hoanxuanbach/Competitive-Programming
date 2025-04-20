#include "cyberland.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define pdi pair<double,int>
#define fi first
#define se second
const double inf=1e18;
double solve(int N, int M, int K, int T, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
    K=min(K,67);
    vector<vector<double>> dist(N,vector<double>(K+1,inf));
    vector<vector<pii>> edge(N);
    for(int i=0;i<M;i++){
        edge[x[i]].push_back({y[i],c[i]});
        edge[y[i]].push_back({x[i],c[i]});
    }
    vector<int> vis(N,0);
    dist[0][0]=0;vis[0]=1;
    queue<int> q;q.push(0);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(arr[u]==0) dist[u][0]=0;
        if(u==T) continue;
        for(auto [v,w]:edge[u]){
            if(vis[v]) continue;
            vis[v]=1;q.push(v);
        }
    }
    bool ok=false;
    double res=1e14;
    for(int k=0;k<=K;k++){
        priority_queue<pdi,vector<pdi>,greater<pdi>> pq;
        for(int i=0;i<N;i++){
            if(i!=T && dist[i][k]!=inf) pq.push({dist[i][k],i});
        }
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(u==T) continue;
            if(d!=dist[u][k]) continue;
            for(auto [v,w]:edge[u]){
                if(arr[u]==2 && k!=K) dist[v][k+1]=min(dist[v][k+1],dist[u][k]/2+w);
                if(dist[u][k]+w<dist[v][k]){
                    dist[v][k]=dist[u][k]+w;
                    pq.push({dist[u][k]+w,v});
                }
            }
        }
        if(dist[T][k]!=inf) ok=true;
        res=min(res,dist[T][k]);
    }
    if(ok) return res;
    else return -1;
}
