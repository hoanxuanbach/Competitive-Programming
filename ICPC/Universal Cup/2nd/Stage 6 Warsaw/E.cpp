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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int base=131;

namespace Tree{
    vector<vector<int>> edge,Min;
    vector<int> lg2,dep,L,R,cn,par,S;
    int pos,cnt;
    int cmp(int u,int v){
        return (dep[u]<dep[v]?u:v);
    }
    int lca(int u,int v){
        u=S[u];v=S[v];
        if(u>v) swap(u,v);
        int p=lg2[v-u+1];
        return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
    }
    int dist(int u,int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    void dfs(int u,int p){
        L[u]=++cnt;
        S[u]=++pos;
        cn[cnt]=u;
        Min[pos][0]=u;
        dep[u]=dep[p]+1;par[u]=p;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);Min[++pos][0]=u;
        }
        R[u]=cnt;
    }
    void init(int n){
        lg2.assign(2*n+1,0);
        dep.assign(n+1,0);
        par.assign(n+1,0);
        S.assign(n+1,0);
        L.assign(n+1,0);
        R.assign(n+1,0);
        cn.assign(n+1,0);
        edge.resize(n+1);
        Min.assign(2*n+1,vector<int>(maxl,0));
    }
    void build(int n){
        init(n);
        for(int i=1;i<n;i++){
            int u,v;cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1,0);
        for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
        for(int i=1;i<20;i++){
            for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
        }
    }
}


int n,up[maxn];
vector<pii> dd[maxn];
ll f[maxn],g[maxn],pre[maxn],w[maxn];

void dfs_down(int u,int p){
    for(int v:Tree::edge[u]){
        if(v==p) continue;
        dfs_down(v,u);
        up[u]=Tree::cmp(up[u],up[v]);
        pre[u]+=pre[v];
        w[u]+=f[v];
    }
    f[u]=w[u]+Tree::R[u]-Tree::L[u]+1+pre[u];
    w[u]-=f[u];
    pre[u]+=w[u];
    pre[up[u]]-=w[u];
    //cout << "f " << u << ' ' << f[u] << ' ' << up[u] << ' ' << pre[u] << ' ' << Tree::R[u]-Tree::L[u]+1 << '\n';
}

int root[maxn];
ll sum[maxn];

void cal_sum(int u,int p){
    sum[u]=sum[p]+w[u];
    //cout << "sum " << u << ' ' << sum[u] << '\n';
    for(int v:Tree::edge[u]) if(v!=p) cal_sum(v,u);
}
ll dist(int u,int v){
    //cout << "dist " << u << ' ' << v << ' ' << Tree::lca(u,v) << '\n';
    return sum[u]+sum[v]-2*sum[Tree::lca(u,v)];
}

namespace Segtree{
    struct node{
        int cl=0,cr=0;
        ll val=0;
        node(int cl=0,int cr=0,ll val=0):cl(cl),cr(cr),val(val){}
        friend node operator+(node a,node b){
            if(!a.cl) return b;
            else if(!b.cl) return a;
            return node(a.cl,b.cr,a.val+b.val+dist(a.cr,b.cl));
        }
        ll total(){
            if(!cl) return 0;
            return (val+dist(cl,cr))/2+w[Tree::lca(cl,cr)];
        }
    }tree[100*maxn];
    int num[100*maxn],L[100*maxn],R[100*maxn],cnt;
    void update(int l,int r,int &id,int p,int val){
        if(!id) id=++cnt;
        if(l==r){
            num[id]+=val;
            if(num[id]) tree[id]=node(Tree::cn[l],Tree::cn[l],0);
            else tree[id]=node();
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,L[id],p,val);
        else update(mid+1,r,R[id],p,val);
        tree[id]=tree[L[id]]+tree[R[id]];
    }
    int merge(int l,int r,int x,int y){
        if(!x || !y) return x|y;
        if(l==r){
            num[x]+=num[y];
            if(num[x]) tree[x]=node(Tree::cn[l],Tree::cn[l],0);
            else tree[x]=node();
            return x;
        }
        int mid=(l+r)>>1;
        L[x]=merge(l,mid,L[x],L[y]);
        R[x]=merge(mid+1,r,R[x],R[y]);
        tree[x]=tree[L[x]]+tree[R[x]];
        return x;
    }
    ll query(int id){
        if(!id) return 0;
        //cout << id << ' ' << tree[id].total() << '\n';
        return tree[id].total();
    }
}

void dfs_up(int u,int p){
    for(int v:Tree::edge[u]){
        if(v==p) continue;
        dfs_up(v,u);
        root[u]=Segtree::merge(1,n,root[u],root[v]);
    }
    for(auto [v,val]:dd[u]) Segtree::update(1,n,root[u],Tree::L[v],val);
    g[u]=Segtree::query(root[u])+n-(Tree::R[u]-Tree::L[u]+1)-pre[u]-f[u];
    //cout << "g " << u << ' ' << pre[u] << ' ' << g[u] << '\n';
}

void dfs_up2(int u,int p){
    g[u]+=g[up[u]]+f[up[u]];
    //cout << u << ' ' << p << '\n';
    for(int v:Tree::edge[u]) if(v!=p) dfs_up2(v,u);
}

void solve(){
    cin >> n;
    Tree::build(n);
    for(int i=1;i<=n;i++) up[i]=i;
    int m;cin >> m;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        int a=Tree::lca(u,v);
        up[u]=Tree::cmp(up[u],a);
        up[v]=Tree::cmp(up[v],a);
        //cout << u << ' ' << v << ' ' << a << '\n';
        dd[a].push_back({u,-2});
        dd[a].push_back({v,-2});
        dd[u].push_back({u,1});
        dd[u].push_back({v,1});
        dd[v].push_back({u,1});
        dd[v].push_back({v,1});
    }
    dfs_down(1,0);cal_sum(1,0);
    dfs_up(1,0);
    g[1]=0;dfs_up2(1,0);
    for(int i=1;i<=n;i++){
        ll res=g[i]-f[1];
        for(int v:Tree::edge[i]) if(v!=Tree::par[i]) res+=f[v];
        cout << res << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
