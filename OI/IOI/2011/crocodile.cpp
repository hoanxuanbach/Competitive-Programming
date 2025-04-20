#include "crocodile.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<long long,int>
#define fi first
#define se second
const long long inf = 1e18;
const int maxn = 1e5+5;

vector<pii> edge[maxn];
long long Min1[maxn],Min2[maxn];

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
    for(int i=0;i<M;i++){
        int u=R[i][0],v=R[i][1];
        edge[u].push_back({L[i],v});
        edge[v].push_back({L[i],u});
    }
    for(int i=0;i<N;i++) Min1[i]=Min2[i]=inf;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=0;i<K;i++){
        Min1[P[i]]=Min2[P[i]]=0;
        pq.push({0,P[i]});
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(Min2[u]!=d) continue;
        for(auto [w,v]:edge[u]){
            if(d+w<Min1[v]){
                if(Min1[v]<Min2[v]){
                    Min2[v]=Min1[v];
                    pq.push({Min2[v],v});
                }
                Min1[v]=d+w;
            }
            else if(d+w<Min2[v]){
                Min2[v]=d+w;
                pq.push({d+w,v});
            }
        }
    }
    return Min2[0];
}


