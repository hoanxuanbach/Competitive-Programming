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
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
void solve(){
    //Input
    int n;cin >> n;
    vector<vector<pii>> edge(n+1);
    vector<int> child(n+1,0),dep(n+1,0),Max(n+1,0);
    vector<bool> used(n+1,false);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,0});
        edge[v].push_back({u,0});
    }

    //Pre_dfs
    function<void(int,int)> dfs_sz = [&](int u,int par){
        child[u]=1;
        for(auto &[v,w]:edge[u]){
            if(v==par) continue;
            dfs_sz(v,u);child[u]+=child[v];
            w=n-child[v];
        }
        for(auto &[v,w]:edge[u]){
            if(v==par) w=child[u];
        }
    };
    dfs_sz(1,0);

    {//Centroid Decomposition
        int sz;
        vector<piii> ver;
        function<void(int,int)> dfs = [&](int u,int par){
            child[u]=1;
            for(auto [v,w]:edge[u]){
                if(v==par || used[v]) continue;
                dfs(v,u);child[u]+=child[v];
            }
        };
        function<int(int,int)> findcen = [&](int u,int par){
            for(auto [v,w]:edge[u]){
                if(v==par || used[v]) continue;
                if(child[v]>sz/2) return findcen(v,u);
            }
            return u;
        };
        function<void(int,int,int,int)> cal = [&](int u,int par,int anc,int s){
            int num=-1;dep[u]=dep[par]+1;
            for(auto [v,w]:edge[u]){
                if(used[v]) continue;
                if(v==par){num=w;continue;}
                cal(v,u,anc,s);
            }
            ver.push_back({num,{dep[u],anc}});
            Max[2*min(s,num)]=max(Max[2*min(s,num)],dep[u]);
        };
        function<void(int)> decompose = [&](int u){
            dfs(u,0);sz=child[u];
            int cen=findcen(u,0);
            ver.clear();dep[cen]=0;
            for(auto [v,w]:edge[cen]){
                if(used[v]) continue;
                cal(v,cen,v,w);
            }
            pii Max1={-inf,-1},Max2={-inf,-1};
            sort(ver.begin(),ver.end(),greater<piii>());
            for(auto [sz,p]:ver){
                if(sz<=n/2){
                    if(Max1.se!=p.se) Max[2*sz]=max(Max[2*sz],p.fi+Max1.fi);
                    else Max[2*sz]=max(Max[2*sz],p.fi+Max2.fi);
                }
                if(p.se==Max1.se) Max1=max(Max1,p);
                else if(p.se==Max2.se){
                    Max2=max(Max2,p);
                    if(Max2.fi>Max1.fi) swap(Max2,Max1);
                }
                else if(p>Max1) Max2=Max1,Max1=p;
                else if(p>Max2) Max2=p;
            }
            used[cen]=true;
            for(auto [v,w]:edge[cen]){
                if(used[v]) continue;
                decompose(v);
            }
        };
        decompose(1);
    }
    for(int i=n-2;i>=1;i--) Max[i]=max(Max[i],Max[i+2]);
    for(int i=1;i<=n;i++) cout << Max[i]+1 << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

