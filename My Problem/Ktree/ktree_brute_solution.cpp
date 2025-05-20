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
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const ll inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
const int S=4;
 
int n,q,c[maxn],dep[maxn];
ll dd[maxn];
vector<pii> edge[maxn];
int par[maxn][maxl];
int L[maxn],R[maxn],T;
 
void dfs(int u,int p){
    dep[u]=dep[p]+1;
    par[u][0]=p;L[u]=++T;
    for(int i=1;i<18;i++) par[u][i]=par[par[u][i-1]][i-1];
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        dd[v]=dd[u]+w;
        dfs(v,u);
    }
    R[u]=T;
}
bool anc(int u,int v){
    return L[v]>=L[u] && L[v]<=R[u];
}
 
int lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    for(int i=0;i<18;i++) if((dep[v]-dep[u])>>i&1) v=par[v][i];
    if(u==v) return u;
    for(int i=17;i>=0;i--){
        if(par[u][i]!=par[v][i]){
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[u][0];
}
 
ll dist(int u,int v){
    return dd[u]+dd[v]-2*dd[lca(u,v)];
}
 
void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> c[i];
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    dfs(1,0);
    //cout << dist(4,1) << '\n';
    for(int i=1;i<=q;i++){
        int op;cin >> op;
        if(op==1){
            int u;cin >> u;
            c[u]^=1;
        }
        else{
            int u,v,t,k;cin >> u >> v >> t >> k;
            vector<ll> d;
            for(int x=1;x<=n;x++) if(anc(u,x) && c[x]==t){
                //cout << "dist " << v << ' ' << x << '\n';
                d.push_back(dist(v,x));
            }
            sort(d.begin(),d.end(),greater<ll>());
            for(int j=0;j<min(k,(int)d.size());j++) cout << d[j] << ' ';
            cout << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
