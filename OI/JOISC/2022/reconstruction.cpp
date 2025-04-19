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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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

void solve(){
    int n,m;cin >> n >> m;
    vector<vector<pii>> edge(n+1);
    vector<piii> e,f;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        e.push_back({w,{u,v}});
    }
    sort(e.begin(),e.end());
    function<piii(int,int,int)> dfs = [&](int u,int t,int p){
        if(u==t) return mpp(inf,mpp(inf,inf));
        for(auto &[v,w]:edge[u]){
            if(v==p) continue;
            piii d=dfs(v,t,u);
            if(d.fi!=-1) return min(d,mpp(w,mpp(u,v)));
        }
        return mpp(-1,mpp(-1,-1));
    };
    auto del = [&](int u,int v,int w){
        edge[u].erase(find(edge[u].begin(),edge[u].end(),mpp(v,w)));
        edge[v].erase(find(edge[v].begin(),edge[v].end(),mpp(u,w)));
    };
    auto add = [&](int u,int v,int w){
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    };
    for(auto x:e){
        int u=x.se.fi,v=x.se.se,w=x.fi;
        piii d=dfs(u,v,0);
        if(d.fi==-1) f.push_back({0,{-1,w}});
        else{
            f.push_back({(d.fi+w+1)>>1,{-2,d.fi+w}});
            del(d.se.fi,d.se.se,d.fi);
        }
        f.push_back({w,{2,-2*w}});
        add(u,v,w);
    }
    sort(f.begin(),f.end());
    long long c=0,k=0;
    int q,cur=0;cin >> q;
    while(q--){
        int x;cin >> x;
        while(cur<(int)f.size() && f[cur].fi<=x) c+=f[cur].se.fi,k+=f[cur++].se.se;
        cout << x*c+k << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
