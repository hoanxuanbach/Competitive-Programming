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
    int n,m;cin >> n >> m;
    int S=ceil(sqrtl(n));
    
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> d(n+1,-1);
    vector<vector<int>> f(S+1);
    function<void(int)> dfs = [&](int u){
        f[d[u]%(S+1)].push_back(u);
        for(int v:g[u]) if(d[v]==-1){
            d[v]=d[u]+1;
            dfs(v);
        }
    };
    d[1]=0;dfs(1);

    int id=0;
    for(int i=1;i<=S;i++) if((int)f[i].size()<(int)f[id].size()) id=i;
    
    f[id].push_back(1);
    sort(f[id].begin(),f[id].end());
    f[id].erase(unique(f[id].begin(),f[id].end()),f[id].end());
    assert((int)f[id].size()<=S);
    cout << (int)f[id].size() << '\n';
    for(int x:f[id]) cout << x << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
