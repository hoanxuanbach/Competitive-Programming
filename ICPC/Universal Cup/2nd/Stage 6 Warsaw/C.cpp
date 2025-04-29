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
const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
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
const int base=131;

int n;
vector<int> edge[maxn];
int head[maxn],par[maxn],L[maxn],R[maxn],pos;
int child[maxn],son[maxn];

void pre_dfs(int u,int p){
    child[u]=1;
    for(int v:edge[u]){
        if(v==p) continue;
        pre_dfs(v,u);child[u]+=child[v];
        if(child[son[u]]<child[v]) son[u]=v;
    }
}

void dfs(int u,int p,int t){
    if(t) head[u]=head[p];
    else head[u]=u;
    L[u]=++pos;par[u]=p;
    if(son[u]) dfs(son[u],u,1);
    for(int v:edge[u]) if(v!=p && v!=son[u]) dfs(v,u,0);
    R[u]=pos;
}

const int inv2 = (mod+1)/2;
namespace Segtree{
    int tree1[4*maxn],tree2[4*maxn],lazy[4*maxn];
    void build(int l,int r,int id){
        tree1[id]=tree2[id]=lazy[id]=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree1[id]=(tree1[id<<1]+tree1[id<<1|1])%mod;
        tree2[id]=(tree2[id<<1]+tree2[id<<1|1])%mod;
    }
    void getnew(int id,int val){
        tree1[id]=tree1[id]*val%mod;
        tree2[id]=tree2[id]*val%mod;
        lazy[id]=lazy[id]*val%mod;
    }
    void pushdown(int id){
        if(lazy[id]==1) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=1;
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree1[id]=(tree1[id<<1]+tree1[id<<1|1])%mod;
        tree2[id]=(tree2[id<<1]+tree2[id<<1|1])%mod;
    }
    void update2(int l,int r,int id,int p,int val){
        if(l==r){
            tree2[id]=(tree2[id]*val)%mod;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) update2(l,mid,id<<1,p,val);
        else update2(mid+1,r,id<<1|1,p,val);
        tree1[id]=(tree1[id<<1]+tree1[id<<1|1])%mod;
        tree2[id]=(tree2[id<<1]+tree2[id<<1|1])%mod;
    }
}


int hld_update(int u,int v,int val){
    while(head[u]!=head[v]){
        if(L[head[u]]>L[head[v]]){
            Segtree::update(1,n,1,L[head[u]],L[u],val);
            u=par[head[u]];
        }
        else{
            Segtree::update(1,n,1,L[head[v]],L[v],val);
            v=par[head[v]];
        }
    }
    if(L[u]>L[v]) swap(u,v);
    Segtree::update(1,n,1,L[u],L[v],val);
    return u;
}

void solve(){
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    pre_dfs(1,0);
    dfs(1,0,0);
    int q;cin >> q;
    Segtree::build(1,n,1);
    for(int i=1;i<=q;i++){
        char c;int u,v;cin >> c >> u >> v;
        int a=hld_update(u,v,(c=='+'?2:inv2));
        Segtree::update2(1,n,1,L[a],(c=='+'?inv2:2));
        cout << (Segtree::tree1[1]-Segtree::tree2[1]+mod)%mod << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

