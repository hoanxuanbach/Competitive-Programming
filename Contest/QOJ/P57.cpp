#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

    vector<int> fac(2*m+1,1),dfac(2*m+1,1);
    for(int i=1;i<=2*m;i++) fac[i]=fac[i-1]*i%mod;
    dfac[2*m]=power(fac[2*m],mod-2);
    for(int i=2*m;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    vector<vector<int>> f(n+1,vector<int>(2*m+1));
    for(int i=0;i<=n;i++){
        f[i][0]=1;
        for(int j=1;j<=2*m;j++) f[i][j]=f[i][j-1]*i%mod;
    }

    vector<vector<pii>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int T=0;
    vector<int> s(n+1,1);
    function<void(int,int)> dfs = [&](int u,int p){
        for(auto [v,w]:g[u]) if(v!=p){
            dfs(v,u);s[u]+=s[v];
            int S=0;
            for(int i=1;i<2*m;i++) S=(S+min(i,2*m-i)*f[s[v]][i]%mod*f[n-s[v]][2*m-i]%mod*dfac[i]%mod*dfac[2*m-i])%mod; 
            T=(T+S*w%mod*fac[2*m])%mod;
        }
    };
    dfs(1,0);
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
