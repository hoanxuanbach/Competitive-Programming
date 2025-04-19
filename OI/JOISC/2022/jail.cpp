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
const int maxn=120005;
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
    int cur,cnt,n;cin >> n;cur=n;cnt=n*34;
    vector<vector<int>> par(n+1,vector<int>(17,0)),edge(cnt+1),adj(n+1);
    vector<int> dep(n+1,0);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    function<void(int,int)> dfs = [&](int u,int p){
        par[u][0]=p;dep[u]=dep[p]+1;
        for(int v:adj[u]){
            if(v==p) continue;
            dfs(v,u);
        }
    };
    dfs(1,0);
    for(int i=1;i<=16;i++){
        for(int j=1;j<=n;j++){
            par[j][i]=par[par[j][i-1]][i-1];
            edge[n*i+j].push_back(n*(i-1)+j);
            edge[n*i+j].push_back(n*(i-1)+par[j][i-1]);
            edge[17*n+n*(i-1)+j].push_back(17*n+n*i+j);
            edge[17*n+n*(i-1)+par[j][i-1]].push_back(17*n+n*i+j);
        }
    }
    auto lca = [=](int u,int v){
        if(dep[u]>dep[v]) swap(u,v);
        for(int i=0;i<=16;i++){
            if((dep[v]-dep[u])&(1<<i)) v=par[v][i];
        }
        if(v==u) return u;
        for(int i=16;i>=0;i--){
            if(par[u][i]!=par[v][i]){
                u=par[u][i];
                v=par[v][i];
            }
        }
        return par[u][0];
    };
    int m;cin >> m;
    while(m--){
        int u,v;cin >> u >> v;
        edge[u].push_back(17*n+v);
        edge[17*n+v].push_back(u);
        int a=par[lca(u,v)][0],s=u,t=v;
        for(int i=16;i>=0;i--){
            if((dep[u]-dep[a])&(1<<i)){
                edge[s].push_back(i*n+u);
                edge[17*n+i*n+u].push_back(17*n+t);
                u=par[u][i];
            }
        }
        for(int i=16;i>=0;i--){
            if((dep[v]-dep[a])&(1<<i)){
                edge[s].push_back(i*n+v);
                edge[17*n+i*n+v].push_back(17*n+t);
                v=par[v][i];
            }
        }
    }
    int pos=0;
    vector<int> low(cnt+1,0),num(cnt+1,0),st;
    vector<bool> inst(cnt+1,false);
    bool ok=true;
    function<void(int)> dfs2 = [&](int u){
        num[u]=low[u]=++pos;
        st.push_back(u);inst[u]=true;
        for(int v:edge[u]){
            if(!num[v]){
                dfs2(v);
                low[u]=min(low[u],low[v]);
            }
            else if(inst[v]) low[u]=min(low[u],num[v]);
        }
        if(low[u]==num[u]){
            int ver=0,v=0;
            do{
                v=st.back();st.pop_back();
                inst[v]=false;ver+=(v<=n);
            }
            while(v!=u);
            if(ver>=2) ok=false;
        }
    };
    for(int i=1;i<=cnt;i++){
        if(!num[i]) dfs2(i);
    }
    cout << (ok?"Yes":"No") << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
