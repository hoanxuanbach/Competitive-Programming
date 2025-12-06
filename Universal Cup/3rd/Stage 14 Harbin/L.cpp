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

    vector<int> sz(n+1),f(n+1);
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int res=0;
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;
        int total=0;
        for(int v:g[u]){
            if(v==p) continue;
            dfs(v,u);sz[u]+=sz[v];
            f[u]=(f[u]+f[v])%mod;
            int val=sz[v]*(n-sz[v])%mod;
            res=(res-val*val%mod+mod)%mod;

            val=(n-sz[v])*(n-sz[v])%mod;
            res=(res+2*val*f[v])%mod;

            res=(res+2*total*f[v])%mod;
            total=(total+f[v])%mod;
        }
        f[u]=(f[u]+sz[u]*sz[u])%mod;
    };
    dfs(1,0);

    int dd=(n*(n-1)/2)%mod;
    dd=dd*dd%mod;
    res=res*power(dd,mod-2)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}