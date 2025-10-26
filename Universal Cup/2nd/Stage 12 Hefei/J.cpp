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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=300005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
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
const int base=131;

int n,m,par[maxn],cur=inf;
vector<int> adj[maxn];
vector<pii> edge[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}

int s1,sn;

void dfs(int u){
    for(auto [v,w]:edge[u]){
        int su=findpar(u),sv=findpar(v);
        if((su==s1 && sv==sn) || (su==sn && sv==s1)) cur=min(cur,w);
    }
    for(int v:adj[u]) dfs(v);
}

void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    s1=findpar(1),sn=findpar(n);
    if(v==s1 || v==sn) swap(u,v);
    par[v]=u;adj[u].push_back(v);
    s1=findpar(1),sn=findpar(n);
    if(u==s1 || u==sn) dfs(v);
}

void solve(){
    cin >> n >> m;
    vector<piii> e(m);
    for(int i=0;i<m;i++){
        cin >> e[i].se.fi >> e[i].se.se >> e[i].fi;
        edge[e[i].se.fi].push_back({e[i].se.se,e[i].fi});
        edge[e[i].se.se].push_back({e[i].se.fi,e[i].fi});
    }
    sort(e.begin(),e.end());
    for(int i=1;i<=n;i++) par[i]=i;
    int res=inf;
    for(auto &[w,x]:e){
        if(x.fi>x.se) swap(x.fi,x.se);
        if(x.fi==1 && x.se==n) res=min(res,w),cur=min(cur,w);
    }
    for(auto &[w,x]:e){
        unions(x.fi,x.se);
        if(findpar(1)==findpar(n)){
            res=min(res,2*w);
            break;
        }
        res=min(res,w+cur);
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
