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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int par[maxn],n,m;
set<int> in[maxn],out[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}


void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) par[i]=i;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        out[u].insert(v);
        in[v].insert(u);
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(out[i].empty()) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        par[u]=0;
        for(int v:in[u]){
            out[v].erase(u);
            if(out[v].empty()) q.push(v);
        }
        in[u].clear();
    }

    for(int i=1;i<=n;i++){
        if((int)out[i].size()==1) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        if((int)out[u].size()!=1) continue;
        int v=*out[u].begin();
        if(u==v) continue;
        out[u].clear();in[v].erase(u);
        if((int)in[u].size()+(int)out[u].size()<(int)in[v].size()+(int)out[v].size()) swap(u,v);
        par[v]=u;
        for(int x:in[v]){
            out[x].erase(v);
            out[x].insert(u);
            in[u].insert(x);
            if((int)out[x].size()==1) q.push(x);
        }
        for(int x:out[v]){
            in[x].erase(v);
            in[x].insert(u);
            out[u].insert(x);
        }
        in[v].clear();out[v].clear();
        if((int)out[u].size()==1) q.push(u);
    }
    int qq;cin >> qq;
    for(int i=1;i<=qq;i++){
        int u,v;cin >> u >> v;
        u=findpar(u);v=findpar(v);
        if(u==0 || v==0 || u==v) cout << 'B';
        else cout << 'H';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
