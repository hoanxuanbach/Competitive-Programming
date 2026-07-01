#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX_T = 10;
const ll MAX_N = 1e18;
const ll INF = 2e18;
const ll K = 2e5;

const int M = 15;
vector<ll> P={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
ll f[K][20],g[K];

void build(){
    for(int i=1;i<K;i++) for(int j=0;j<=M;j++) f[i][j]=INF;
    f[1][0]=1;
    for(int i=1;i<K;i++) for(int j=0;j<M;j++) if(f[i][j]!=INF){
        int t=1;
        ll d=f[i][j];
        while(d<=INF/P[j] && i*(t+1)<K){
            d*=P[j];
            int ni=i*(t+1);
            f[ni][j+1]=min(f[ni][j+1],d);
            t++;
        }
    }
    for(int i=1;i<K;i++){
        g[i]=INF;
        for(int j=0;j<=M;j++) g[i]=min(g[i],f[i][j]);
        if(i<=20) cout << i << ' ' << g[i] << '\n';
    }
};

signed main(){
    build();
}