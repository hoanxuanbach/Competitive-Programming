#include "Bitaro.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll,int>
#define pii pair<int,int>
#define fi first
#define se second


namespace Bitaro{
    const ll inf=1e18;
    const int maxn = 10005;
    const int maxm = 20005;
    int lst[maxn],f[maxm],up[maxn];
    pli dist[maxn];
    vector<pii> edge[maxn];

    void bitaro(int N, int M, int Q, int K,vector<int> A, vector<int> B,
            vector<ll> C, std::vector<int> T, std::vector<int> X,
            string S){
        for(int i=0;i<M;i++){
            edge[A[i]].push_back({B[i],i});
            edge[B[i]].push_back({A[i],i});
        }
        int P=0;
        for(int i=0;i<K;i+=10){
            ll num=0;
            for(int j=0;j<=40;j++) num+=(S[P++]-'0')*(1LL<<j);
            for(int j=min(i+10,K)-1;j>=i;j--){
                f[j]=num%(Q+1),num/=(Q+1);
                //cout << '*' << j << ' ' << f[j] << '\n';
            }
        }
        for(int i=0;i<N;i++) up[i]=-1;
        for(int i=0;i<Q;i++){
            for(int j=0;j<14;j++) lst[i]+=(S[P++]-'0')*(1<<j);
            for(int j=0;j<K;j++) C[X[j]]=(f[j]==i+1?1:inf);
            priority_queue<pli,vector<pli>,greater<pli>> pq;
            for(int j=0;j<N;j++) dist[j]={inf,-1};
            dist[lst[i]]={0,-1};
            pq.push({0,lst[i]});
            while(!pq.empty()){
                auto [d,u]=pq.top();pq.pop();
                if(dist[u].fi!=d) continue;
                //if(i==2) cout << "pq " << d << ' ' << u << '\n';
                for(auto [v,id]:edge[u]){
                    pli nd={d+C[id],id};
                    if(nd.fi<dist[v].fi) pq.push({nd.fi,v});
                    dist[v]=min(dist[v],nd);
                }
            }
            //if(i==2){
            //cout << T[i] << ' ' << lst[i] << '\n';
            //for(int j=0;j<N;j++) cout << dist[j].fi << ' ' << dist[j].se << '\n';
            //}
            //if(i!=2){
            int u=T[i];
            vector<int> ans;
            while(u!=0){
                if(up[u]==-1) up[u]=dist[u].se;
                ans.push_back(up[u]);
                //cout << '*' << u << ' ' << up[u] << '\n';
                u^=A[up[u]]^B[up[u]];
            }
            reverse(ans.begin(),ans.end());
            answer(ans);
            //}
        }
    }
}

void bitaro(int N, int M, int Q, int K, std::vector<int> A, std::vector<int> B,
            std::vector<long long> C, std::vector<int> T, std::vector<int> X,
            std::string s) {
    Bitaro::bitaro(N,M,Q,K,A,B,C,T,X,s);
}
