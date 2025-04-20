#include "dreaming.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf=1e9;
#define pii pair<int,int>
#define fi first
#define se second
vector<pii> edge[maxn];
int Max[maxn],d[maxn],res;
bool vis[maxn];

void dfs(int u,int p){
    vis[u]=true;
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        if(Max[v]+w>Max[u]){
            d[u]=Max[u];
            Max[u]=Max[v]+w;
        }
        else if(Max[v]+w>d[u]) d[u]=Max[v]+w;
    }
    res=max(res,Max[u]+d[u]);
}
int Min=inf;
void redfs(int u,int p,int t){
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        int nxt=max(t,(Max[v]+w==Max[u]?d[u]:Max[u]))+w;
        redfs(v,u,nxt);
    }
    Max[u]=max(Max[u],t);
    Min=min(Min,Max[u]);
}
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    for(int i=0;i<M;i++){
        edge[A[i]].push_back({B[i],T[i]});
        edge[B[i]].push_back({A[i],T[i]});
    }
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=0;i<N;i++){
        if(!vis[i]){
            dfs(i,0);Min=inf;
            redfs(i,0,0);
            pq.push(Min);
        }
    }
    while((int)pq.size()>3) pq.pop();
    if(pq.empty()) return res;
    int s1=pq.top();pq.pop();
    if(pq.empty()) return res;
    int s2=pq.top();pq.pop();
    if(pq.empty()) return max(res,s1+s2+L);
    int s3=pq.top();pq.pop();
    return max(res,max(s2+s3+L,s1+s2+2*L));
}
