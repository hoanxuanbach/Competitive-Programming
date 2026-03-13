#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
    }
    return res;
}

void solve(){
    int n;cin >> n;
    vector<int> c(n+1),s(n+1);
    for(int i=1;i<=n;i++) cin >> c[i],s[c[i]]++;
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> p(n+1,1);
    for(int i=1;i<=n;i++) p[i]=p[i-1]*2%mod;
    int total=0;
    for(int i=1;i<=n;i++) total=(total+p[s[i]]-1)%mod;

    int res=0;
    vector<int> A(n+1),B(n+1);
    vector<map<int,int>> f(n+1);
    function<void(int,int)> dfs = [&](int u,int par){
        B[u]=total;

        int T=0;
        for(int v:g[u]){
            if(v==par) continue;
            dfs(v,u);
            T=(T+A[v])%mod;
            if((int)f[v].size()>f[u].size()){
                f[u].swap(f[v]);
                A[u]=A[v];
                B[u]=B[v];
            }
            for(auto [x,d]:f[v]){
                int k=f[u][x];
                //cout << "add " << u << ' ' << v << ' ' << x << ' ' << k << ' ' << d << '\n';
                A[u]=(A[u]-p[k]+1+mod)%mod;
                B[u]=(B[u]-p[s[x]-k]+1+mod)%mod;
                f[u][x]+=d;k+=d;
                A[u]=(A[u]+p[k]-1+mod)%mod;
                B[u]=(B[u]+p[s[x]-k]-1+mod)%mod;
            }
        }
        int x=c[u],d=1;
        int k=f[u][x];
        A[u]=(A[u]-p[k]+1+mod)%mod;
        B[u]=(B[u]-p[s[x]-k]+1+mod)%mod;
        f[u][x]+=d;k+=d;
        A[u]=(A[u]+p[k]-1+mod)%mod;
        B[u]=(B[u]+p[s[x]-k]-1+mod)%mod;

        res=(res+B[u]*(A[u]+mod-T))%mod;
        for(int v:g[u]){
            if(v==par) continue;
            int k=(B[v]-B[u]-T+A[v]+2*mod)%mod;
            res=(res+k*A[v])%mod;
        }
    };
    dfs(1,0);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}