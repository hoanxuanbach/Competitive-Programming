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
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
vector<pii> edge[maxn];
int n,dp[maxn][2],add[maxn];
void dfs(int u,int par){
    int Max=-inf;
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        dfs(v.fi,u);
        int x=max(dp[v.fi][0],dp[v.fi][1]+v.se);
        Max=max(Max,dp[v.fi][0]+v.se-x);dp[u][0]+=x;
    }
    dp[u][1]=dp[u][0]+Max;
}
int dfs2(int u,int par){
    int Max=add[u]+dp[u][0];
    int Max1=-inf,Max2=-inf;
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        int x=max(dp[v.fi][0],dp[v.fi][1]+v.se),y=dp[v.fi][0]+v.se;
        if(y-x>Max1){Max2=Max1;Max1=y-x;}
        else if(y-x>Max2) Max2=y-x;
    }
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        int x=max(dp[v.fi][0],dp[v.fi][1]+v.se),y=dp[v.fi][0]+v.se;
        add[v.fi]=max(add[v.fi],add[u]+dp[u][0]-x+max(0LL,v.se+(y-x==Max1?Max2:Max1)));
        int cur=add[u]+dp[u][0]-x+v.se;
        for(pii w:edge[v.fi]){
            if(w.fi==u) continue;
            int x2=max(dp[w.fi][0],dp[w.fi][1]+w.se);
            add[w.fi]=max(add[w.fi],cur+w.se+dp[v.fi][0]-x2);
        }
        Max=max(Max,dfs2(v.fi,u));
    }
    return Max;
}
void solve(){
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    dfs(1,0);
    cout << dfs2(1,0) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
