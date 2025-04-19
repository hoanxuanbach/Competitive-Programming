#include "Aoi.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll,int>
#define pii pair<int,int>
#define fi first
#define se second

namespace Aoi{
    const int maxn = 10005;
    const int maxm = 20005;
    const ll inf = 1e18;
    pli dist[maxn];
    vector<pii> edge[maxn];
    bool vis[maxn],del[maxm];
    int lst[maxn],f[maxm];

    string aoi(int N, int M, int Q, int K, vector<int> A, vector<int> B,
               vector<ll> C, vector<int> T, vector<int> X){
        for(int i=0;i<K;i++) del[X[i]]=true;
        for(int i=0;i<M;i++){
            edge[A[i]].push_back({B[i],i});
            edge[B[i]].push_back({A[i],i});
        }
        for(int i=0;i<N;i++) dist[i]={inf,-1};
        priority_queue<pli,vector<pli>,greater<pli>> pq;
        dist[0]={0,-1};pq.push({0,0});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(dist[u].fi!=d) continue;
            for(auto [v,id]:edge[u]){
                pli nd={d+C[id],id};
                if(nd.fi<dist[v].fi) pq.push({nd.fi,v});
                dist[v]=min(dist[v],nd);
            }
        }
        vis[0]=true;
        for(int i=0;i<Q;i++){
            int u=T[i];
            while(!vis[u]){
                int id=dist[u].se;
                vis[u]=true;
                if(del[id]) f[id]=i+1;
                //cout << "dist " << u << ' ' << id << '\n';
                u^=A[id]^B[id];
            }
            lst[i]=u;
        }
        string S;
        for(int i=0;i<K;i+=10){
            ll num=0;
            for(int j=i;j<min(i+10,K);j++) num=num*(Q+1)+f[X[j]];
            for(int j=0;j<=40;j++) S+=char('0'+(num>>j&1));
        }
        for(int i=0;i<Q;i++){
            for(int j=0;j<14;j++) S+=char('0'+(lst[i]>>j&1));
        }
        return S;
    }
}

std::string aoi(int N, int M, int Q, int K, std::vector<int> A,
                std::vector<int> B, std::vector<long long> C,
                std::vector<int> T, std::vector<int> X) {
    return Aoi::aoi(N,M,Q,K,A,B,C,T,X);
}
