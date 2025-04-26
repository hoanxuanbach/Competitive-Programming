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

int n,a[maxn],d[maxn],res[maxn],total=0;
vector<int> edge[maxn];

void dfs(int u,int p){
    for(int v:edge[u]) if(v!=p) dfs(v,u);
    if(p){
        int k=min(a[u],a[p]);
        a[u]-=k;a[p]-=k;total+=2*k;
        if(a[u]) d[p]=u;
    }
}
void dfs2(int u,int p){
    res[u]=total;
    for(int v:edge[u]){
        if(v==p) continue;
        if(a[u]){
            a[u]--;total++;
            dfs2(v,u);
            a[u]++;total--;
        }
        else if(d[v]){
            int x=d[v];
            a[x]--;total++;
            dfs2(v,u);
            a[x]++;total--;
        }
        else{
            a[v]++;total--;
            dfs2(v,u);
            a[v]--;total++;
        }
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;u++;v++;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    total=2*(n-1);
    for(int i=1;i<=n;i++) a[i]-=(int)edge[i].size();
    dfs(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

