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
    /*
    int N = 1000;
    vector<vector<int>> g(N);
    for(int i=2;i<N;i++){
        function<void(int)> dfs = [&](int u){
            g[i].push_back(u);
            if(g[u].empty()) return;
            int x=g[u].back();g[u].pop_back();
            dfs(x);
        };
        dfs(i-1);
        if(g[i].back()==1) cout << i << '\n';
        sort(g[i].begin(),g[i].end());
    }
    */
    int N=1,X=1;
    for(int i=1;i<=17;i++) N*=10,X*=9;
    int total=X;
    while(X<N){
        int d=1;
        while(X+2*d<=N) d*=2;
        X+=d;total+=X;
    }
    cout << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

