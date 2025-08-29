#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
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

struct DSU{
    int par[maxn],r[maxn],x[maxn],c[maxn];
    void init(int n){
        for(int i=1;i<=n;i++){par[i]=i;r[i]=1;c[i]=0;x[i]=0;}
    }
    pii findpar(int u){
        if(u!=par[u]){
            pii a=findpar(par[u]);
            return {a.fi,a.se^x[u]};
        }
        return {u,x[u]};
    }
    void unions(int u,int v){
        pii pu=findpar(u),pv=findpar(v);
        if(pu.fi==pv.fi){
            if(pu.se==pv.se) c[pu.fi]=1;
            return;
        }
        if(r[pu.fi]<r[pv.fi]) swap(pu,pv);
        par[pv.fi]=pu.fi;r[pu.fi]+=r[pv.fi];c[pu.fi]|=c[pv.fi];
        if((pv.se^x[pu.fi])==pu.se) x[pv.fi]^=1;
    }
}dsu;

void solve(){
    int n,m,K;cin >> n >> m >> K;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    dsu.init(n);

    vector<vector<int>> edge(n+1);
    vector<int> vis(n+1,0),d(n+1,0);
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    int T=0;
    function<void(int,int)> dfs = [&](int u,int p){
        vis[u]=++T;
        for(int v:edge[u]){
            if(!vis[v]) dfs(v,u),d[u]+=d[v];
            else if(v!=p && vis[v]<vis[u]){
                dsu.unions(u,v);
                d[v]--;d[u]++;
            }
        }
        if(d[u]) dsu.unions(u,p);
    };
    dfs(1,0);


    vector<vector<int>> f(n+1);
    for(int i=1;i<=n;i++) f[dsu.findpar(i).fi].push_back(i);
    int res=1;
    for(int i=1;i<=n;i++){
        if(f[i].empty()) continue;
        bool cc=dsu.c[i];

        int A=-1,B=-1;
        for(int x:f[i]){
            if(a[x]==-1) continue;
            if(A==-1) A=a[x];
            else if(A!=a[x]) B=a[x];
        }
        if(B!=-1){
            res=0;
        }
        if(A!=-1){
            if(cc && A!=0) res=0;
        }
        else res=(res*(cc?1:K))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
