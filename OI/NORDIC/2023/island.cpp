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

set<int> s[maxn];
int n,par[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(s[u].find(v)!=s[u].end()) return false;
    if((int)s[u].size()<(int)s[v].size()) swap(u,v);
    par[v]=u;
    for(int x:s[v]){
        s[u].insert(x);
        s[x].erase(v);
        s[x].insert(u);
    }
    return true;
}

void solve(){
    int n,m,q;cin >> n >> m >> q;
    for(int i=1;i<=n;i++) par[i]=i;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        s[u].insert(v);
        s[v].insert(u);
    }
    for(int i=1;i<=q;i++){
        int u,v;cin >> u >> v;
        if(unions(u,v)) cout << "APPROVE\n";
        else cout << "REFUSE\n";
    }
}

signed main(){    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}