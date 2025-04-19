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
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
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

void solve(){
    int n,m,ans=0;cin >> n >> m;
    vector<set<pii>> s(n);
    vector<set<int>> t(n);
    vector<int> par(n),sz(n);
    for(int i=0;i<n;i++) par[i]=i,sz[i]=1;
    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    function<void(int,int)> add = [&](int u,int v){
        int x=findpar(u),y=findpar(v);
        if(x==y) return;
        auto it=s[y].lower_bound({x,0});
        if(it!=s[y].end() && it->fi==x){
            if(sz[y]>sz[x]) swap(x,y);
            vector<pii> nw;
            for(pii p:s[y]){
                ans-=sz[p.fi];
                t[p.fi].erase(p.se);
                if(p.fi!=x) nw.push_back({p.se,p.fi});
            }
            ans+=sz[y]*(2*sz[x]+(int)t[x].size()-(int)t[y].size());
            for(int p:t[y]){
                int pr=findpar(p);
                s[pr].erase({y,p});
                if(pr!=x) nw.push_back({p,x});
            }
            par[y]=x;sz[x]+=sz[y];
            for(pii p:nw) add(p.fi,p.se);
        }
        else if(t[y].find(u)==t[y].end()){
            ans+=sz[y];
            s[x].insert({y,u});
            t[y].insert(u);
        }
    };
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        u--;v--;add(u,v);
        cout << ans << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
