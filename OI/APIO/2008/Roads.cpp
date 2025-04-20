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

int p[maxn];
int findpar(int u){return p[u]<0?u:p[u]=findpar(p[u]);}
void init(int n){
    for(int i=1;i<=n;i++) p[i]=-1;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    if(p[u]>p[v]) swap(u,v);
    p[u]+=p[v];p[v]=u;
    return true;
}

void solve(){
    int n,m,k;cin >> n >> m >> k;
    vector<pii> e0,e1;
    for(int i=1;i<=m;i++){
        int u,v,c;cin >> u >> v >> c;
        if(c) e1.push_back({u,v});
        else e0.push_back({u,v});
    }
    int s0=0;
    vector<pii> c0;

    init(n);
    for(auto [u,v]:e0) s0+=unions(u,v);

    init(n);
    for(auto [u,v]:e1) unions(u,v);
    for(auto [u,v]:e0) if(unions(u,v)) c0.push_back({u,v});

    if(k>s0 || k<(int)c0.size()){
        cout << "no solution\n";
        return;
    }
    init(n);
    vector<piii> ans;
    for(auto [u,v]:c0) if(unions(u,v)) ans.push_back({0,{u,v}});
    k-=(int)c0.size();
    for(auto [u,v]:e0) if(k && unions(u,v)) ans.push_back({0,{u,v}}),k--;
    for(auto [u,v]:e1) if(unions(u,v)) ans.push_back({1,{u,v}});

    for(auto [c,x]:ans) cout << x.fi << ' ' << x.se << ' ' << c << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

