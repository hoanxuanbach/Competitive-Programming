#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N=1;
    vector<vector<int>> adj(8);
    auto add = [&](int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    vector<int> T;
    for(int i=1;i<=7;i++){
        T.push_back(4);
        add(i,i%7+1);
        add(0,i);
    }

    int K;cin >> K;

    for(int I=2;I<=K/2;I++){
        int S=(int)T.size();

        vector<int> nT;
        for(int i=0;i<S;i++){
            for(int j=0;j<T[i]-2;j++){
                adj.emplace_back();
                add(N+i,N+S+(int)nT.size());
                nT.push_back(4);
            }
            adj.emplace_back();
            add(N+i,N+S+(int)nT.size());
            add(N+(i+1)%S,N+S+(int)nT.size());
            nT.push_back(3);
        }
        swap(T,nT);
        N+=S;S=(int)T.size();
        for(int i=0;i<S;i++) add(N+i,N+(i+1)%S);
    }

    N+=(int)T.size();

    vector<vector<int>> d(N,vector<int>(K+1,0));
    d[0][0]=1;
    for(int k=1;k<=K;k++){
        for(int x=0;x<N;x++) for(int y:adj[x]) d[y][k]+=d[x][k-1];
    }
    cout << d[0][K] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
