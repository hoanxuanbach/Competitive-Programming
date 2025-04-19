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
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,s[maxn],t[maxn],res;

struct event{
    int pu,pv;
    bool cur;
};

namespace DSU{
    bool check=true;
    int par[maxn],d[maxn],sz[maxn];
    vector<event> E;
    void reset(){
        check=true;E.clear();
        for(int i=1;i<=n;i++) par[i]=i,d[i]=0,sz[i]=1;
    }
    pii findpar(int u){
        if(u!=par[u]){
            pii x=findpar(par[u]);
            return {x.fi,x.se^d[u]};
        }
        return {u,0};
    }

    void unions(int u,int v,int t){
        auto [pu,du]=findpar(u);
        auto [pv,dv]=findpar(v);
        if(pu==pv){
            E.push_back({pu,pv,check});
            if((du^t)!=dv) check=false;
            return;
        }
        if(sz[pu]<sz[pv]) swap(pu,pv),swap(du,dv);
        E.push_back({pu,pv,check});
        par[pv]=pu;sz[pu]+=sz[pv];
        d[pv]^=du^dv^t;
    }
    void roll_back(){
        event e=E.back();
        E.pop_back();
        check=e.cur;
        int pu=e.pu,pv=e.pv;
        if(pu==pv) return;
        d[pv]=0;par[pv]=pv;
        sz[pu]-=sz[pv];
    }
}

void dnc(int l,int r){
    if(l==r){
        DSU::unions(s[l],t[l],0);
        res+=DSU::check;
        DSU::roll_back();
        return;
    }
    int mid=(l+r)>>1;
    for(int i=r;i>mid;i--) DSU::unions(s[i],t[i],1);
    dnc(l,mid);
    for(int i=r;i>mid;i--) DSU::roll_back();
    for(int i=l;i<=mid;i++) DSU::unions(s[i],t[i],1);
    dnc(mid+1,r);
    for(int i=l;i<=mid;i++) DSU::roll_back();
}

void solve(){
    cin >> n >> m;
    DSU::reset();
    for(int i=1;i<=m;i++) cin >> s[i] >> t[i];
    dnc(1,m);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
