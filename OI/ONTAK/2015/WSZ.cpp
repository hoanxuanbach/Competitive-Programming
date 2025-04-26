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
const int inf=1e9;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
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

int n,m,c[maxn];
vector<int> edge[maxn];
vector<int> ans;

bool vis[maxn];
int dp[maxn][2];

void dfs(int u,int p){
    vis[u]=true;
    int all=0,sum=0,Min=inf;
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        sum+=dp[v][0];
        all+=min(dp[v][0],dp[v][1]);
        if(dp[v][1]!=inf) Min=min(Min,dp[v][1]-dp[v][0]);
    }
    dp[u][0]=all+1;
    if(c[u]) dp[u][1]=sum;
    else{
        dp[u][0]=min(dp[u][0],sum);
        dp[u][1]=min(inf,sum+Min);
    }
}

void trace(int u,int p,int t){
    int all=0,sum=0,Min=inf;
    for(int v:edge[u]){
        if(v==p) continue;
        sum+=dp[v][0];
        all+=min(dp[v][0],dp[v][1]);
        if(dp[v][1]!=inf) Min=min(Min,dp[v][1]-dp[v][0]);
    }
    if(t){
        for(int v:edge[u]){
            if(v==p) continue;
            if(dp[v][1]!=inf && Min==dp[v][1]-dp[v][0] && !c[u]) Min=inf,trace(v,u,1);
            else trace(v,u,0);
        }
    }
    else{
        if(dp[u][0]==all+1) ans.push_back(u);
        for(int v:edge[u]){
            if(v==p) continue;
            if(dp[u][0]==all+1 && dp[v][0]>dp[v][1]) trace(v,u,1);
            else trace(v,u,0);
        }
    }
}

void solve(){
    int p;cin >> n >> m >> p;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        if(u==p) c[v]++;
        else if(v==p) c[u]++;
        else{
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    }
    for(int i=1;i<=n;i++){
        if(c[i]>=2){
            ans.push_back(i);
            edge[i].clear();c[i]=0;
        }
        else{
            vector<int> nw;
            for(int x:edge[i]) if(c[x]<=1) nw.push_back(x);
            swap(nw,edge[i]);
        }
    }
    int sum=0;
    for(int i=1;i<=n;i++) if(!vis[i]){
        dfs(i,0);
        //sum+=min(dp[i][0],dp[i][1]);
        if(dp[i][0]<dp[i][1]) trace(i,0,0);
        else trace(i,0,1);
    }
    cout << (int)ans.size() << '\n';
    for(int v:ans) cout << v << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
