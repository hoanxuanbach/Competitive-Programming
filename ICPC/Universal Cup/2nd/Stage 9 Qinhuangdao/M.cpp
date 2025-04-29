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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=5005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
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

int p2[maxn],cc[maxn];
bool vis[maxn];
vector<pii> e;
int n,dp[maxn][2],d[maxn];
vector<int> edge[maxn];

int pre[maxn],suf[maxn];
void dfs(int u,int p){
    vis[u]=true;
    dp[u][0]=0;
    dp[u][1]=1;
    for(int v:edge[u]){
        if(vis[v]) continue;
        dfs(v,u);
        pre[v]=dp[u][1];
        dp[u][1]=dp[u][1]*(dp[v][1]+dp[v][0]*2)%mod;
    }
    reverse(edge[u].begin(),edge[u].end());
    int cur=1;
    for(int v:edge[u]){
        if(v==p) continue;
        dp[u][0]=(dp[u][0]+pre[v]*cur%mod*dp[v][0])%mod;
        cur=cur*(dp[v][1]+dp[v][0]*2)%mod;
    }
    dp[u][0]=dp[u][0]*p2[d[u]]%mod;
    if(d[u]) dp[u][0]=(dp[u][0]+dp[u][1]*d[u]%mod*p2[d[u]-1])%mod;
    dp[u][1]=dp[u][1]*p2[d[u]]%mod;
}

void cal(){
    for(int i=1;i<=n;i++){
        edge[i].clear(),d[i]=0;
        vis[i]=false;
    }
    for(pii x:e){
        if(cc[x.fi] && cc[x.se]){
            edge[x.fi].push_back(x.se);
            edge[x.se].push_back(x.fi);
        }
        else if(cc[x.fi]) d[x.fi]++;
        else if(cc[x.se]) d[x.se]++;
    }
    int res=1;
    for(int i=1;i<=n;i++) if(!vis[i] && cc[i]){
        dfs(i,0);
        res=res*dp[i][0]%mod;
    }
    cout << res << '\n';
}

void solve(){
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        e.push_back({u,v});
    }
    p2[0]=1;
    for(int i=1;i<=n;i++) p2[i]=p2[i-1]*2%mod;
    for(int i=1;i<n;i++){
        int u;cin >> u;
        cc[u]=1;cal();
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
