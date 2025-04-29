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
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,scc[maxn],num[maxn];
vector<int> edge[maxn],rev_edge[maxn],order;
int vis[maxn],cnt=0;

void dfs(int u){
    vis[u]=1;
    for(int v:edge[u]) if(!vis[v]) dfs(v);
    order.push_back(u);
}
void dfs2(int u){
    scc[u]=cnt;num[cnt]++;
    for(int v:rev_edge[u]) if(!scc[v]) dfs2(v);
}
void solve(){
    int n,m;cin >> n >> m;
    for(int i=1;i<=m;i++){
        int p=0;
        for(int j=1;j<=n;j++){
            int x;cin >> x;
            if(p){
                edge[p].push_back(x);
                rev_edge[x].push_back(p);
            }
            p=x;
        }
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
    for(int i=1;i<=n;i++){
        int u=order[n-i];
        if(scc[u]) continue;
        cnt++;dfs2(u);
    }
    for(int i=1;i<=n;i++) edge[i].clear();
    for(int i=1;i<=n;i++){
        for(int v:rev_edge[i]){
            if(scc[v]==scc[i]) continue;
            edge[scc[v]].push_back(scc[i]);
        }
    }
    order.clear();
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
    for(int i=1;i<(int)order.size();i++) num[order[i]]+=num[order[i-1]];
    for(int i=1;i<=n;i++) cout << num[scc[i]]-1 << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
