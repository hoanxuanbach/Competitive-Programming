#include "dungeons.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 400005;
const int K=8;
const int L=24;
const ll inf = 1e18;

int N,nxt[K][L][maxn];
ll sum[K][L][maxn],mn[K][L][maxn],T[maxn],pw[K+5];
vector<int> S,P,W,D;

void init(int n, std::vector<int> s, std::vector<int> p, std::vector<int> w, std::vector<int> l) {
	N=n;S=s;P=p;W=w;D=l;
    S.push_back(0);
    W.push_back(N);

    pw[0]=1;
    for(int i=1;i<=K;i++) pw[i]=pw[i-1]*8;
    for(int i=N-1;i>=0;i--) T[i]=T[W[i]]+S[i];
    for(int t=0;t<K;t++){
        int H=pw[t];
        nxt[t][0][N]=N;
        sum[t][0][N]=0;
        mn[t][0][N]=inf;
        for(int u=0;u<N;u++){
            if(S[u]<=H){
                nxt[t][0][u]=W[u];
                sum[t][0][u]=S[u];
                mn[t][0][u]=inf;
            }
            else{
                nxt[t][0][u]=D[u];
                sum[t][0][u]=P[u];
                mn[t][0][u]=S[u];
            }
        }
        for(int i=1;i<L;i++) for(int u=0;u<=N;u++){
            nxt[t][i][u]=nxt[t][i-1][nxt[t][i-1][u]];
            sum[t][i][u]=sum[t][i-1][u]+sum[t][i-1][nxt[t][i-1][u]];
            mn[t][i][u]=min(mn[t][i-1][u],mn[t][i-1][nxt[t][i-1][u]]-sum[t][i-1][u]);
        }
    }
}

ll simulate(int x, int z) {
    ll d=z;
    for(int t=0;t<K;t++){
        while(true){
            if(d>=pw[t+1] || x==N) break;
            for(int i=L-1;i>=0;i--){
                if(mn[t][i][x]>d){
                    d+=sum[t][i][x];
                    x=nxt[t][i][x];
                }
            }
            d+=S[x];x=W[x];
        }
    }
    return d+T[x];
}

