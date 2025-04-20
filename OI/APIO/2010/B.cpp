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
const long long inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
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
const int base=101;

struct node{
    int dd=0,Max=0;
    node(){}
    friend node operator+(node a,node b){
        node res;
        res.Max=max({a.Max,b.Max,a.dd+b.dd});
        res.dd=max(a.dd,b.dd);
        return res;
    }
}dp[maxn];

int n,k,res=0;
vector<int> edge[maxn],dist[maxn];
node suf[maxn];

void dfs(int u,int p){
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        dist[u].push_back(++dp[v].dd);
        dp[u]=dp[u]+dp[v];
    }
}

void redfs(int u,int p,node val){
    dist[u].push_back(val.dd);
    node cur;
    for(int i=(int)edge[u].size()-1;i>=0;i--){
        int v=edge[u][i];
        if(v==p) continue;
        suf[v]=cur;
        cur=cur+dp[v];
    }
    cur=node();
    for(int v:edge[u]){
        if(v==p) continue;
        node nxt=cur+suf[v]+val;
        res=max(res,nxt.Max+dp[v].Max);
        nxt.dd++;redfs(v,u,nxt);
        cur=cur+dp[v];
    }
    sort(dist[u].begin(),dist[u].end(),greater<int>());
    int num=0;
    for(int i=0;i<(int)dist[u].size() && i<4;i++) num+=dist[u][i];
    res=max(res,num);
}


void solve(){
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    if(k==1){
        cout << 2*(n-1)-dp[1].Max+1 << '\n';
        return;
    }
    redfs(1,0,node());
    cout << 2*(n-1)-res+2 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
