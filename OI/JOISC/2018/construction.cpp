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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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

namespace BIT{
    int n;
    vector<int> bit;
    void init(int _n=0){n=_n;bit.assign(n+1,0);}
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}
int ans=0;
vector<pii> ss;
namespace Segtree{
    int n=0;
    vector<int> tree;
    void init(int _n=0){
        n=_n;
        tree.assign(4*n,0);
    }
    void pushdown(int id){
        if(tree[id]==0) return;
        tree[id<<1]=tree[id<<1|1]=tree[id];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr && tree[id]){
            ans+=BIT::query(tree[id]-1)*(r-l+1);
            BIT::update(tree[id],r-l+1);
            ss.push_back({tree[id],r-l+1});
            tree[id]=val;
            return;
        }
        else if(l==r){tree[id]=val;return;}
        pushdown(id);
        int mid=(l+r)>>1;
        update(mid+1,r,id<<1|1,tl,tr,val);update(l,mid,id<<1,tl,tr,val);
        tree[id]=(tree[id<<1]==tree[id<<1|1])*tree[id<<1];
    }
};
void solve(){
    int n;cin >> n;
    vector<vector<int>> edge(n+1);
    vector<int> L(n+1),head(n+1,0),child(n+1,1),son(n+1,0),par(n+1,0),c(n+1);
    vector<pii> e(n);
    int pos=0;

    vector<int> com;
    for(int i=1;i<=n;i++) cin >> c[i],com.push_back(c[i]);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=1;i<=n;i++) c[i]=lower_bound(com.begin(),com.end(),c[i])-com.begin()+1;

    BIT::init(n);Segtree::init(n);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
        e[i]={u,v};
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
    auto hld_update = [=](int u,int v,int val){
        while(head[u]!=head[v]){
            if(L[head[u]]<L[head[v]]) swap(u,v);
            Segtree::update(1,n,1,L[head[u]],L[u],val);
            u=par[head[u]];
        }
        Segtree::update(1,n,1,min(L[u],L[v]),max(L[u],L[v]),val);
    };
    hld_update(1,1,c[1]);
    for(int i=1;i<n;i++){
        int u=e[i].fi,v=e[i].se;
        if(par[v]!=u) swap(u,v);
        ans=0;ss.clear();hld_update(1,v,c[v]);
        for(auto &[x,cnt]:ss){
            //cout << '{' << x << ' ' << cnt << "} ";
            BIT::update(x,-cnt);
        }
        //cout << '\n';
        cout << ans << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
