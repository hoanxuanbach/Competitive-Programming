#include "testlib.h"
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
    }
};

pair<int,ll> get_divisor(ll LIM){
    pair<int,ll> ret={-1,-1};
    for(int i=1;i<K;i++) if(g[i]<=LIM) ret={i,g[i]};
    return ret; 
};
ll construct(ll LIM,int K){
    while(g[K]>LIM) K++;
    return g[K];
};

void test_generator(int T,string mode,int subtask){
    ll LIM = MAX_N;
    if(subtask == 1) LIM = 1e3;
    else if(subtask == 2) LIM = 1e12;
    if(mode == "random"){   
        ll N = rnd.next(1LL,LIM);
        cout << N << '\n';
    }
    else{
        auto [K,S] = get_divisor(LIM);
        if(mode == "max" && T==0) cout << S << '\n';
        else if(mode == "max") cout << construct(LIM,rnd.next((K+1)/2,K)) << '\n';
        else cout << construct(LIM,rnd.next(1,K)) << '\n';
    }
}
 
 
int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    
    const string mode = opt<string>("mode");
    const int subtask = opt<int>("subtask");
    //cout << mode << ' ' << subtask << endl;
    build();
    int T=MAX_T;
    cout << T << '\n';
    while(T--) test_generator(T,mode,subtask);
    return 0;
}
