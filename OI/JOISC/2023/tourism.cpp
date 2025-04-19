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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
namespace BIT{
    int n;
    vector<int> bit;
    void init(int _n=0){n=_n;bit.assign(n+1,0);}
    void update(int x,int val){
        x=n+1-x;
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;x=n+1-x;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}
namespace Segtree{
    int n=0;
    vector<int> tree;
    void init(int _n=0){
        n=_n;
        tree.assign(4*n,0);
    }
    void pushdown(int id){
        if(tree[id]==-1) return;
        tree[id<<1]=tree[id<<1|1]=tree[id];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr && tree[id]>=0){
            if(tree[id]) BIT::update(tree[id],-(r-l+1));
            BIT::update(tree[id]=val,r-l+1);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=(tree[id<<1]==tree[id<<1|1]?tree[id<<1]:-1);
    }
};
void solve(){
    int n,m,q;cin >> n >> m >> q;
    vector<vector<int>> edge(n+1);
    vector<int> L(n+1),head(n+1,0),child(n+1,1),son(n+1,0),par(n+1,0);
    vector<int> ans(q+1,1),c(m+1);
    vector<vector<pii>> v(m+1);
    int pos=0;
    BIT::init(m);Segtree::init(n);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    function<void(int,int)> dfs = [&](int u,int p){
        par[u]=p;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);child[u]+=child[v];
            son[u]=(child[son[u]]<=child[v]?v:son[u]);
        }
    };
    dfs(1,0);
    function<void(int,int)> hld_dfs = [&](int u,int p){
        L[u]=++pos;head[u]+=(!head[u])*u;
        if(son[u]){
            head[son[u]]=head[u];
            hld_dfs(son[u],u);
        }
        for(int v:edge[u]){
            if(v==p || v==son[u]) continue;
            hld_dfs(v,u);
        }
    };
    hld_dfs(1,0);
    for(int i=1;i<=m;i++) cin >> c[i];
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        if(l<r) v[r].push_back({l,i});
    }
    auto hld_update = [=](int u,int v,int val){
        while(head[u]!=head[v]){
            if(L[head[u]]<L[head[v]]) swap(u,v);
            Segtree::update(1,n,1,L[head[u]],L[u],val);
            u=par[head[u]];
        }
        Segtree::update(1,n,1,min(L[u],L[v]),max(L[u],L[v]),val);
    };
    for(int i=2;i<=m;i++){
        hld_update(c[i],c[i-1],i-1);
        for(auto [l,id]:v[i]) ans[id]=BIT::query(l);
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
