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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9+5;
const int mod=998244353;
const int maxn=300005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,d[maxn],child[maxn],sz,dep[maxn];
bool used[maxn];
vector<pii> edge[maxn],ver;

int num;
vector<int> adj[maxn*maxl];

void dfs_sz(int u,int par){
    child[u]=1;
    for(auto [v,w]:edge[u]){
        if(v==par || used[v]) continue;
        dfs_sz(v,u);child[u]+=child[v];
    }
}

int findcen(int u,int par){
    for(auto [v,w]:edge[u]){
        if(v==par || used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}

void dfs(int u,int par){
    ver.push_back({dep[u],u});
    for(auto [v,w]:edge[u]){
        if(v==par || used[v]) continue;
        dep[v]=min(inf,dep[u]+w);
        dfs(v,u);
    }
}

void decompose(int u){
    dfs_sz(u,0);sz=child[u];
    int cen=findcen(u,0);
    ver.clear();used[cen]=true;
    dep[cen]=0;dfs(cen,0);

    sort(ver.begin(),ver.end());
    int Max=0;
    for(int i=0;i<(int)ver.size();i++){
        int pos=upper_bound(ver.begin(),ver.end(),mpp(d[ver[i].se]-ver[i].fi,n))-ver.begin();
        Max=max(Max,pos);
        if(pos) adj[ver[i].se].push_back(num+pos);
    }
    for(int i=0;i<Max;i++){
        if(i) adj[num+i+1].push_back(num+i);
        adj[num+i+1].push_back(ver[i].se);
    }
    num+=Max;
    for(auto [v,w]:edge[cen]) if(!used[v]) decompose(v);
}

bool vis[maxn*maxl];
int scc[maxn*maxl],deg[maxn*maxl],cnt;
vector<int> rev_adj[maxn*maxl],order;

void dfs1(int u){
    vis[u]=true;
    for(int v:adj[u]){
        rev_adj[v].push_back(u);
        if(!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u){
    scc[u]=cnt;
    for(int v:rev_adj[u]) if(!scc[v]) dfs2(v);
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> d[i];
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    num=n;
    decompose(1);
    for(int i=1;i<=num;i++) if(!vis[i]) dfs1(i);
    for(int i=1;i<=num;i++){
        int u=order[num-i];
        if(!scc[u]){
            cnt++;
            dfs2(u);
        }
    }
    for(int i=1;i<=num;i++){
        for(int v:adj[i]){
            if(scc[i]!=scc[v]) deg[scc[v]]++;
        }
    }
    int res=0;
    for(int i=1;i<=cnt;i++) if(!deg[i]) res++;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
