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
const int inf=1e9+5;
const int mod=998244353;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

struct DSU{
    set<int> s[maxn];
    int par[maxn];
    int findpar(int u){
        if(u!=par[u]) return findpar(par[u]);
        return u;
    }
    void init(int n){
        for(int i=1;i<=n;i++){
            par[i]=i;
            s[i].insert(i);
        }
    }
    pii unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u==v) return {-1,-1};
        if((int)s[u].size()<(int)s[v].size()) swap(u,v);
        par[v]=u;
        //cout << "T1 " << u << ' ' << v << '\n';
        for(int x:s[v]) s[u].insert(x);
        return {u,v};
    }
}T0,T1;

void solve(){
    int n,m;cin >> n >> m;
    vector<piii> e0,e1;
    T0.init(n);T1.init(n);
    int res=2*inf;
    for(int i=1;i<=m;i++){
        int u,v,w,c;cin >> u >> v >> w >> c;
        if(c) e1.push_back({w,{u,v}});
        else e0.push_back({w,{u,v}});
    }
    sort(e0.begin(),e0.end());
    sort(e1.begin(),e1.end());

    vector<piii> ne;
    for(int i=0;i<(int)e1.size();i++){
        pii p=T1.unions(e1[i].se.fi,e1[i].se.se);
        if(p.fi!=-1) ne.push_back({e1[i].fi,p});
    }
    for(int i=1;i<=n;i++) T0.s[i]={T1.findpar(i)};

    int p=(int)ne.size()-1;
    for(int i=0;i<(int)e0.size();i++){
        int u=e0[i].se.fi,v=e0[i].se.se;
        u=T0.findpar(u);v=T0.findpar(v);
        if(u==v) continue;
        if((int)T0.s[u].size()<(int)T0.s[v].size()) swap(u,v);

        while(!T0.s[v].empty()){
            int x=*T0.s[v].begin();
            if(T0.s[u].find(x)!=T0.s[u].end()){

                int cu=ne[p].se.fi,cv=ne[p].se.se;
                if(T1.findpar(cv)!=cu) swap(cu,cv);
                //cout << '*' << cu << ' ' << cv << '\n';
                T1.par[cv]=cv;

                for(int d:T1.s[cv]){
                    T1.s[cu].erase(d);
                    int k=T0.findpar(d);
                    if(k==v){
                        if(T0.s[k].find(cu)!=T0.s[k].end()){
                            T0.s[k].erase(cu);
                            T0.s[k].insert(cv);
                        }
                        else{
                            T0.s[u].erase(cu);
                            T0.s[u].insert(cv);
                        }
                    }
                    else{
                        T0.s[k].erase(cu);
                        T0.s[k].insert(cv);
                    }
                }
                p--;
            }
            else{
                T0.s[u].insert(x);
                T0.s[v].erase(T0.s[v].begin());
            }
        }
        T0.par[v]=u;
        //cout << u << ' ' << v << ' ' << p << '\n';
        if(p!=(int)ne.size()-1) res=min(res,e0[i].fi+ne[p+1].fi);
    }
    cout << (res==2*inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
