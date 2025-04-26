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
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,Max=0,deg[maxn];
vector<int> edge[maxn];
vector<int> dq[maxn];

void dfs(int u){
    for(int v:edge[u]){
        dfs(v);
        if((int)dq[u].size()<(int)dq[v].size()) dq[u].swap(dq[v]);
        int su=(int)dq[u].size(),sv=(int)dq[v].size();
        for(int i=1;i<=sv;i++){
            dq[u][su-i]+=dq[v][sv-i];
            Max=max(Max,dq[u][su-i]-i-1);
        }
    }
    dq[u].push_back(1);
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        int sz;cin >> sz;
        for(int j=0;j<sz;j++){
            int u;cin >> u;
            deg[u]++;
            edge[i].push_back(u);
        }
    }
    for(int i=1;i<=n;i++) if(!deg[i]) dfs(i);
    cout << Max << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
