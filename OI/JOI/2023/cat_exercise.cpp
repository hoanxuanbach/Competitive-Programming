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
- insert(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
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
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;
namespace Tree{
    vector<vector<int>> edge,Min;
    vector<int> lg2,dep,L,R;
    int pos;
    int cmp(int u,int v){
        return (dep[u]<dep[v]?u:v);
    }
    int lca(int u,int v){
        u=L[u];v=L[v];
        if(u>v) swap(u,v);
        int p=lg2[v-u+1];
        return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
    }
    int dist(int u,int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    void dfs(int u,int p){
        L[u]=++pos;Min[pos][0]=u;
        dep[u]=dep[p]+1;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);Min[++pos][0]=u;
        }
        R[u]=pos;
    }
    void init(int n){
        lg2.assign(2*n+1,0);
        dep.assign(n+1,0);
        L.assign(n+1,0);
        R.assign(n+1,0);
        edge.resize(n+1);
        Min.assign(2*n+1,vector<int>(maxl,0));
    }
    void build(int n){
        init(n);
        for(int i=1;i<n;i++){
            int u,v;cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1,0);
        for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
        for(int i=1;i<20;i++){
            for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
        }
    }
}
void solve(){
    int n;cin >> n;
    vector<pii> p(n);
    vector<int> dp(n+1,0),par(n+1),Max(n+1,0);
    for(int i=1;i<=n;i++) par[i]=i;
    for(int i=0;i<n;i++){cin >> p[i].fi;p[i].se=i+1;}
    sort(p.begin(),p.end());Tree::build(n);
    function<int(int)> findpar = [&](int u){
        if(par[u]!=u) return par[u]=findpar(par[u]);
        return u;
    };
    for(auto &[x,u]:p){
        Max[u]=x;
        for(int v:Tree::edge[u]){
            if(Max[v]==0) continue;
            v=findpar(v);par[v]=u;
            dp[u]=max(dp[u],dp[v]+Tree::dist(u,v));
        }
    }
    cout << dp[p.back().se] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
