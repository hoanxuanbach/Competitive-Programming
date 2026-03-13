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
    int n;cin >> n;
    vector<vector<pii>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    vector<int> sz(n+1),T(n+1),res(2*n);
    vector<vector<int>> dp(n+1);
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;
        vector<array<int,3>> f(2*n,{-inf,-inf,-inf});
        f[0][0]=0;

        for(auto [v,w]:g[u]){
            if(v==p) continue;
            dfs(v,u);T[v]+=w;T[u]+=T[v];
            for(int k=2;k>=0;k--){
                if(k<2){
                    for(int i=0;i<=2*sz[u]-2;i++) for(int j=0;j<=2*sz[v]-2;j++) f[i+j+1][k+1]=max(f[i+j+1][k+1],f[i][k]+dp[v][j]+w);
                }
                for(int i=2*sz[u]-2;i>=0;i--) f[i+2*sz[v]][k]=max(f[i+2*sz[v]][k],f[i][k]+2*T[v]); 
            }
            sz[u]+=sz[v];
        }

        dp[u].assign(2*sz[u],-inf);
        //cout << "dfs " << u << '\n';
        for(int i=0;i<=2*sz[u]-2;i++){
            res[i]=max({res[i],f[i][0],f[i][1],f[i][2]});
            dp[u][i]=max({dp[u][i],f[i][0],f[i][1]});
            //cout << f[i][0] << ' ' << f[i][1] << ' ' << f[i][2] << '\n';
        }
        //cout << '\n';
    };
    dfs(1,0);
    for(int i=0;i<=2*n-2;i++) cout << 2*T[1]-res[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}