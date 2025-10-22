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
    int n;cin >> n;
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<array<int,2>> dp(n+1,{0,0});
    function<void(int,int)> dfs = [&](int u,int p){
        dp[u][0]=1;
        dp[u][1]=0;
        bool leaf=true;
        for(int v:g[u]){
            if(v==p) continue;
            dfs(v,u);
            leaf=false;
            dp[u][1]=(dp[u][1]*(dp[v][0]+dp[v][1])+dp[u][0]*dp[v][1])%mod;
            dp[u][0]=dp[u][0]*(dp[v][0]+dp[v][1])%mod;
        }
        if(leaf) dp[u][1]=1;
    };
    dfs(1,0);
    cout << dp[1][0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
