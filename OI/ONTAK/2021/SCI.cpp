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
const int maxn=505;
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

int n,m,k;
vector<pii> edge[maxn];
int dp[maxn][(1<<8)+5];

void cal(int mask){
    for(int i=1;i<=n;i++){
        dp[i][mask]=inf;
        for(int j=mask;j;j=(j-1)&mask){
            if(j==mask) continue;
            dp[i][mask]=min(dp[i][mask],dp[i][mask^j]+dp[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto [v,w]:edge[i]){
            if(w>0) continue;
            w=-w;
            if(mask&(1<<w)) dp[i][mask]=min(dp[i][mask],dp[v][mask^(1<<w)]);
        }
    }
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=1;i<=n;i++) pq.push({dp[i][mask],i});
    while(!pq.empty()){
        int u=pq.top().se,d=pq.top().fi;pq.pop();
        if(dp[u][mask]!=d) continue;
        for(auto [v,w]:edge[u]){
            int nd=dp[u][mask]+max(w,0LL);
            if(nd<dp[v][mask]){
                dp[v][mask]=nd;
                pq.push({nd,v});
            }
        }
    }

}

void solve(){
    cin >> n >> m >> k;
    for(int i=0;i<k;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,-i});
        edge[v].push_back({u,-i});
    }
    for(int i=0;i<m-k;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    for(int i=1;i<(1<<k);i++) cal(i);
    int res=inf;
    for(int i=1;i<=n;i++) res=min(res,dp[i][(1<<k)-1]);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
