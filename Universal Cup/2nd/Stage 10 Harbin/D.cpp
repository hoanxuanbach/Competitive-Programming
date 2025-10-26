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
const int base=101;

int w[maxa+5],p[maxa+5];
int par[maxa+5];
vector<pii> e[35];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}

bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return par[v]=u,true;
}

void solve(){
    for(int i=0;i<30;i++) e[i].clear();
    int l,r;cin >> l >> r;
    for(int i=l;i<=r;i++) par[i]=i;
    int res=0;
    for(int i=1;i<=r;i++){
        int c=0;
        for(int j=((l-1)/i+1)*i;j<=r;j+=i) if(w[j]<w[c]) c=j;
        for(int j=((l-1)/i+1)*i;j<=r;j+=i) if(c!=j) e[w[c]+w[j]-w[i]].push_back({c,j});
    }
    for(int i=0;i<30;i++){
        for(auto [u,v]:e[i]) if(unions(u,v)) res+=i;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    w[0]=inf;
    for(int i=2;i<=maxa;i++){
        if(!p[i]){
            for(int j=i;j<=maxa;j+=i) p[j]=i;
        }
        int d=i;
        while(d>1){
            int j=p[d];w[i]++;
            while(d%j==0) d/=j;
        }
    }
    int test=1;cin >> test;
    while(test--) solve();
}
