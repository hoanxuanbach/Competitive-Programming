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
 
const int maxn = 3e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int n;cin >> n;combi(3000000);
    vector<array<int,3>> a(n);
    for(int i=0;i<n;i++){
        int S=0;
        for(int j=0;j<3;j++) cin >> a[i][j],S+=a[i][j];
        for(int j=0;j<3;j++) a[i][j]=a[i][j]*inv[S]%mod;
    }
    vector<vector<pii>> g(n);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;u--;v--;
        g[u].push_back({v,1});
        g[v].push_back({u,0});
    }   

    vector<int> sz(n),tmp(3*n+1,0);
    vector<vector<int>> f(n,vector<int>(3*n+1,0));
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=3;
        for(int i=1;i<=3;i++) f[u][i]=a[u][i-1]*i%mod;
        for(auto [v,k]:g[u]){
            if(v==p) continue;
            dfs(v,u);
            for(int i=1;i<=sz[u];i++) for(int j=1;j<=sz[v];j++){
                int val=f[u][i]*f[v][j]%mod;
                if(k) tmp[i+j]=(tmp[i+j]+val)%mod;
                else tmp[i+j]=(tmp[i+j]+mod-val)%mod,tmp[i]=(tmp[i]+val)%mod;
            }
            sz[u]+=sz[v];
            for(int i=1;i<=sz[u];i++) f[u][i]=tmp[i],tmp[i]=0;
        }
        for(int i=1;i<=sz[u];i++) f[u][i]=f[u][i]*inv[i]%mod;
    };
    dfs(0,0);
    int res=0;
    for(int i=1;i<=sz[0];i++) res=(res+f[0][i])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
