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
#pragma GCC target("popcnt,lzcnt")

#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;

int d[(1<<18)+5],f[(1<<18)+5];
int par[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return par[v]=u,true;
}
int cc,s1[maxn],s2[maxn];
vector<int> edge[maxn];

void dfs(int u,int par){
    s1[++cc]=u;s2[cc]=par;
    for(int v:edge[u]){
        if(v!=par) dfs(v,u);
    }
}

void solve(){
    int n;cin >> n;
    memset(d,-1,sizeof(d));
    memset(f,0,sizeof(f));
    queue<int> q;
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        edge[i].clear();
        f[a]=par[i]=i;d[a]=0;
        q.push(a);
    }
    int sum=0;
    vector<piii> e;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<18;i++){
            int v=u^(1<<i);
            if(d[v]==-1){
                d[v]=d[u]+1;f[v]=f[u];
                q.push(v);
            }
            else if(f[u]!=f[v]) e.push_back({d[u]+d[v]+1,{f[u],f[v]}});
        }
    }
    sort(e.begin(),e.end());
    for(auto [d,p]:e){
        if(unions(p.fi,p.se)){
            sum+=d;
            edge[p.fi].push_back(p.se);
            edge[p.se].push_back(p.fi);
        }
    }
    cc=0;dfs(1,1);
    cout << sum << '\n';
    for(int i=1;i<=n;i++) cout << s1[i] << ' ';
    cout << '\n';
    for(int i=1;i<=n;i++) cout << s2[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
