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
const int mod=1e9+7;
const int maxn=300005;
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
const int base=131;

int n,dp[maxn];
vector<int> f[maxn],g[maxn];
vector<int> edge[maxn];

void dfs(int u,int p){
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
    }
    sort(edge[u].begin(),edge[u].end(),[](int x,int y){
        return (int)f[x].size()<(int)f[y].size();
    });
    vector<int> F(1,1),G(1,0);
    for(int v:edge[u]){
        if(v==p) continue;
        int sz=(int)f[v].size();
        vector<int> nF(1<<sz),nG(1<<sz);
        for(int i=0;i<(int)F.size();i++){
            nF[i]=(nF[i]+F[i]*dp[v])%mod;
            nG[i]=(nG[i]+G[i]*dp[v])%mod;
            for(int j=0;j<sz;j++){
                if(i>>j&1) continue;
                nF[i|(1<<j)]=(nF[i|(1<<j)]+F[i]*f[v][j])%mod;
                if(i>(1<<j)) nG[i|(1<<j)]=(nG[i|(1<<j)]+G[i]*f[v][j])%mod;
                else nG[i|(1<<j)]=(nG[i|(1<<j)]+F[i]*g[v][j])%mod;
            }
        }
        swap(F,nF);swap(G,nG);
    }
    int sz=log2((int)F.size());
    f[u].assign(sz+1,0);
    g[u].assign(sz+1,0);
    for(int i=0;i<=sz;i++){
        int mask=(1<<i)-1;
        dp[u]=(dp[u]+G[mask]+F[mask])%mod;
        f[u][i]=(f[u][i]+F[mask])%mod;
        g[u][i]=(g[u][i]+F[mask])%mod;
        for(int j=0;j<i-1;j++) g[u][j]=(g[u][j]+G[mask^(1<<j)]+F[mask^(1<<j)])%mod;
    }
    while(!f[u].back() && !g[u].back()) f[u].pop_back(),g[u].pop_back();
}

void solve(){
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    cout << dp[1] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
