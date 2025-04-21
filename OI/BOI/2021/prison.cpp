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
const int maxn=2000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;
 
vector<int> edge[maxn],Max[maxn];
int par[maxn],dep[maxn],ans=0;
pii cur[maxn];
 
int n,D,T,a[maxn],L[maxn];
 
void dfs(int u,int p){
    dep[u]=dep[p]+1;
    cur[u]={dep[u],u};
    for(int v:edge[u]){
        dfs(v,u);
        cur[u]=max(cur[u],cur[v]);
    }
    Max[cur[u].fi-dep[u]+1].push_back(u);
}
 
void update(int u){
    do{
        dep[u]=0;
        if(u!=n+1) ans--;
        u=par[u];
    }while(dep[u]);
}
 
void solve(){
    cin >> n >> D >> T;
    vector<int> v;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]<=T){
            while(!v.empty() && v.back()+T-a[v.back()]<=i+T-a[i]) v.pop_back();
            v.push_back(i);
        }
        while(!v.empty() && v.back()+T-a[v.back()]<i) v.pop_back();
        if(!v.empty()) L[i]=v.back();
    }
    v.clear();
    v.push_back(n+1);
    for(int i=n;i>=1;i--){
        if(L[i]) ans++;
        if(L[i]==i || !L[i]) continue;
        while(!v.empty() && i<L[v.back()]) v.pop_back();
        edge[v.back()].push_back(i);par[i]=v.back();
        v.push_back(i);
    }
    dfs(n+1,0);
    for(int i=n;i>=1;i--){
        for(int u:Max[i]){
            if(D==0) break;
            if(!dep[u]) continue;
            update(cur[u].se);D--;
        }
    }
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}