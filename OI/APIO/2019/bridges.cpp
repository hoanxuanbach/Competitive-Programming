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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int B=350;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

struct DSU{
    int sz[maxn],par[maxn];
    vector<pii> event;
    void build(int n){
        event.clear();
        for(int i=1;i<=n;i++) sz[i]=1,par[i]=i;
    }
    int findpar(int u){
        if(u!=par[u]) return findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u==v){
            event.push_back({-1,-1});
            return;
        }
        if(sz[u]<sz[v]) swap(u,v);
        par[v]=u;sz[u]+=sz[v];
        event.push_back({u,v});
    }
    void roll_back(){
        auto &[u,v]=event.back();event.pop_back();
        if(u==-1) return;
        par[v]=v;sz[u]-=sz[v];
    }
}dsu;

int n,m,q,sz,res[maxn];
piii qq[maxn],E[maxn];
vector<int> com,pos[maxn];
bool cn[maxn];
int cc[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        E[i]={w,{u,v}};
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> qq[i].fi >> qq[i].se.fi >> qq[i].se.se;
        if(qq[i].fi==2) com.push_back(qq[i].se.se);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=1;i<=m;i++) E[i].fi=upper_bound(com.begin(),com.end(),E[i].fi)-com.begin();
    for(int i=1;i<=q;i++) qq[i].se.se=upper_bound(com.begin(),com.end(),qq[i].se.se)-com.begin();
    for(int t=1;t<=q;t+=B){
        int l=t,r=min(t+B-1,q);
        for(int i=1;i<=sz;i++) pos[i].clear();
        for(int i=1;i<=m;i++) pos[E[i].fi].push_back(i);

        vector<int> p;
        for(int i=l;i<=r;i++){
            if(qq[i].fi==1){
                if(!cn[qq[i].se.fi]) p.push_back(qq[i].se.fi);
                cn[qq[i].se.fi]=true;
            }
            else pos[qq[i].se.se].push_back(-i);
        }
        dsu.build(n);
        for(int x=sz;x>=1;x--){
            for(int id:pos[x]){
                if(id>0){
                    if(!cn[id]){
                        //cout << id << '\n';
                        dsu.unions(E[id].se.fi,E[id].se.se);
                    }
                }
                else{
                    //cout << id << '\n';
                    id=-id;
                    for(int k:p) cc[k]=E[k].fi;
                    for(int i=l;i<=id;i++) if(qq[i].fi==1) cc[qq[i].se.fi]=qq[i].se.se;
                    for(int k:p){
                        //cout << k << ' ' << cc[k] << '\n';
                        if(cc[k]>=qq[id].se.se) dsu.unions(E[k].se.fi,E[k].se.se);
                    }
                    res[id]=dsu.sz[dsu.findpar(qq[id].se.fi)];
                    for(int k:p) if(cc[k]>=qq[id].se.se) dsu.roll_back();
                }
            }
        }
        for(int i=l;i<=r;i++) if(qq[i].fi==1){
            cn[qq[i].se.fi]=false;
            E[qq[i].se.fi].fi=qq[i].se.se;
        }
    }
    for(int i=1;i<=q;i++) if(qq[i].fi==2) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
