// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=250005;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,m,par[maxn],d[maxn];
vector<pii> edge[maxn];
vector<piii> add;
bool vis[maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    par[v]=u;return true;
}
void dfs(int u){
    vis[u]=true;
    for(pii v:edge[u]){
        if(vis[v.first]) continue;
        d[v.first]=d[u]^v.second;
        dfs(v.first);
    }
}
int basis[65],cnt=0;
void update(int x){
    //cout << x << '\n';
    for(int i=60;i>=0;i--){
        if(x&(1LL<<i)){
            if(!basis[i]){
                basis[i]=x;
                return;
            }
            x^=basis[i];
        }
    }
}
bool tt[maxn];
vector<pii> adj[maxn];
vector<piii> e;
vector<int> ver;
void dfs2(int u){
    tt[u]=true;ver.push_back(u);
    for(pii v:adj[u]){
        if(v.first>u) e.push_back({v.second,{v.first,u}});
        if(tt[v.first]) continue;
        dfs2(v.first);
    }
}
void solve(){
    cnt++;
    cin >> n >> m;
    for(int i=1;i<=n;i++){par[i]=i;adj[i].clear();tt[i]=false;vis[i]=false;edge[i].clear();d[i]=0;}
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    int ans=0;
    for(int s=1;s<=n;s++){
        if(!tt[s]){
            e.clear();add.clear();ver.clear();
            for(int i=0;i<=60;i++) basis[i]=0;
            dfs2(s);
            for(piii x:e){
                if(unions(x.se.fi,x.se.se)){
                    edge[x.se.fi].push_back({x.se.se,x.fi});
                    edge[x.se.se].push_back({x.se.fi,x.fi});
                }
                else add.push_back({x.fi,{x.se.fi,x.se.se}});
            }
            dfs(s);
            for(piii x:add) update(x.fi^d[x.se.fi]^d[x.se.se]);
            int res=0;
            for(int i=60;i>=0;i--){
                if(basis[i]==0) continue;
                if(((res>>i)&1)==0) res^=basis[i];
            }
            ans=max(ans,res);
        }
    }
    cout << "Case #" << cnt << ": " << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
