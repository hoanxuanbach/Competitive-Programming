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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const ll inf=1e18;
const int maxn=400005;
const int maxl=20;
struct node{
    pair<ll,int> Max1={-inf,-1},Max2={-inf,-1};
    node(){}
    friend node operator+(node a,pair<ll,int> x){
        if(x>a.Max1){
            if(x.se==a.Max1.se) a.Max1=x;
            else{a.Max2=a.Max1;a.Max1=x;}
        }
        else if(x>a.Max2 && x.se!=a.Max1.se) a.Max2=x;
        return a;
    }
    ll query(int p){
        if(p==Max1.se) return Max2.fi;
        else return Max1.fi;
    }
};
int n;
ll ans=-inf;
namespace Centroid{
    vector<pii> edge[maxn];
    int child[maxn],sz,dad[maxn];
    int Min[2*maxn][maxl],lg2[2*maxn],pos,L[maxn];
    ll dep[maxn];
    node Max[maxn];
    bool used[maxn];
    int cmp(int u,int v){
        return (L[u]<L[v]?u:v);
    }
    void pre_dfs(int u,int par){
        Min[++pos][0]=u;L[u]=pos;
        for(pii v:edge[u]){
            if(v.fi==par) continue;
            dep[v.fi]=dep[u]+v.se;
            pre_dfs(v.fi,u);
            Min[++pos][0]=u;
        }
    }
    int lca(int u,int v){
        u=L[u];v=L[v];
        if(u>v) swap(u,v);
        int p=lg2[v-u+1];
        return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
    }
    ll dist(int u,int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    void dfs(int u,int par){
        child[u]=1;
        for(pii v:edge[u]){
            if(v.fi==par || used[v.fi]) continue;
            dfs(v.fi,u);child[u]+=child[v.fi];
        }
    }
    int findcen(int u,int par){
        for(pii v:edge[u]){
            if(v.fi==par || used[v.fi]) continue;
            if(child[v.fi]>sz/2) return findcen(v.fi,u);
        }
        return u;
    }
    void decompose(int u,int par){
        dfs(u,par);sz=child[u];
        int cen=findcen(u,par);
        dad[cen]=par;used[cen]=true;
        for(pii v:edge[cen]){
            if(v.fi==par || used[v.fi]) continue;
            decompose(v.fi,cen);
        }
    }
    void del(int u){
        while(u){Max[u]=node();u=dad[u];}
    }
    void add(int u){
        int x=u,pre=u;
        while(x){
            Max[x]=Max[x]+make_pair(dist(u,x)+dep[u],pre);
            pre=x;x=dad[x];
        }
    }
    ll query(int u){
        ll res=-inf;
        int x=u,pre=u;
        while(x){
            res=max(res,dist(u,x)+Max[x].query(pre));
            pre=x;x=dad[x];
        }
        return (res+dep[u])/2;
    }
    void build(){
        for(int i=1;i<n;i++){
            int u,v,w;cin >> u >> v >> w;
            edge[u].push_back({v,w});
            edge[v].push_back({u,w});
        }
        pre_dfs(1,0);
        decompose(1,0);
        for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
        for(int i=1;i<20;i++){
            for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
        }
    }
}
ll dep[maxn],cur;
int child[maxn],son[maxn];
vector<pii> edge[maxn];
vector<int> ver;
void pre_dfs(int u,int par){
    child[u]=1;
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        dep[v.fi]=dep[u]+v.se;
        pre_dfs(v.fi,u);child[u]+=child[v.fi];
        if(child[v.fi]>child[son[u]]) son[u]=v.fi;
    }
}
void cal(int u,int par){
    ans=max(ans,Centroid::query(u)-cur);
    ver.push_back(u);
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        cal(v.fi,u);
    }
}
void del(int u,int par){
    Centroid::del(u);
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        del(v.fi,u);
    }
}
void dfs(int u,int par,int t){
    for(pii v:edge[u]){
        if(v.fi==par || v.fi==son[u]) continue;
        dfs(v.fi,u,1);
    }
    if(son[u]) dfs(son[u],u,0);
    cur=dep[u];
    for(pii v:edge[u]){
        if(v.fi==par || v.fi==son[u]) continue;
        ver.clear();cal(v.fi,u);
        for(int x:ver) Centroid::add(x);
    }
    ans=max(ans,Centroid::dep[u]-cur);
    ans=max(ans,Centroid::query(u)-cur);
    Centroid::add(u);
    if(t) del(u,par);
}
void solve(){
    cin >> n;
    Centroid::build();
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    pre_dfs(1,0);
    dfs(1,0,0);
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

