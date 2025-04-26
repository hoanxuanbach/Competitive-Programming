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
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
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

int L[maxn],R[maxn],cn[maxn],head[maxn],child[maxn],son[maxn],p[maxn],pos=0;
int n,lt[maxn],rt[maxn],num[maxn],b[maxn],c[maxn];
vector<int> edge[maxn];
bool check;

void reset(){
    check=true;pos=0;
    for(int i=1;i<=n;i++){
        edge[i].clear();
        L[i]=R[i]=cn[i]=head[i]=child[i]=son[i]=p[i]=0;
        lt[i]=rt[i]=num[i]=b[i]=c[i]=0;
    }
}

namespace Segtree{
    pii tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id]={c[cn[l]],cn[l]};
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {inf,-1};
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
    void del(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl || tree[id].fi==inf) return;
        if(l==r){
            tree[id]={inf,-1};
            return;
        }
        int mid=(l+r)>>1;
        del(l,mid,id<<1,tl,tr);del(mid+1,r,id<<1|1,tl,tr);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
};

namespace Segtree2{
    pii tree[4*maxn];
    int lazy[4*maxn];
    void getnew(int id,int val){
        tree[id].fi-=val;
        lazy[id]+=val;
    }
    void pushdown(int id){
        if(lazy[id]==0) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    void build(int l,int r,int id){
        lazy[id]=0;
        if(l==r){
            tree[id]={rt[cn[l]],cn[l]};
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
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
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {inf,-1};
        if(tl<=l && r<=tr) return tree[id];
        pushdown(id);
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
    pii query(int a,int u){
        pii Min={inf,-1};
        while(L[head[u]]>L[a]){
            Min=min(Min,query(1,n,1,L[head[u]],L[u]));
            u=p[head[u]];
        }
        if(L[u]>L[a]) Min=min(Min,query(1,n,1,L[a]+1,L[u]));
        return Min;
    }
    void update(int a,int u,int val){
        while(L[head[u]]>L[a]){
            update(1,n,1,L[head[u]],L[u],val);
            u=p[head[u]];
        }
        if(L[u]>L[a]) update(1,n,1,L[a]+1,L[u],val);
    }
}

void hld_dfs(int u,int t){
    L[u]=++pos;cn[pos]=u;
    if(!t) head[u]=u;
    else head[u]=head[p[u]];
    if(son[u]) hld_dfs(son[u],1);
    for(int v:edge[u]){
        if(v==son[u]) continue;
        hld_dfs(v,0);
    }
    R[u]=pos;
}

void dfs_cal(int u){
    for(int v:edge[u]) dfs_cal(v);
    //cout << u << ' ' << b[u] << '\n';
    while(b[u]){
        pii x=Segtree::query(1,n,1,L[u],R[u]);
        if(x.fi>=c[u]) break;
        pii y=Segtree2::query(u,x.se);
        if(y.fi==0) Segtree::del(1,n,1,L[x.se],R[x.se]);
        else{
            int k=min(y.fi,b[u]);
            b[u]-=k;b[x.se]+=k;
            //cout << u << ' ' << x.se << '\n';
            Segtree2::update(u,x.se,k);
        }
    }
}

void dfs(int u){
    num[u]=b[u]=0;
    child[u]=1;
    for(int v:edge[u]){
        dfs(v);
        num[u]+=num[v];
        child[u]+=child[v];
        if(child[son[u]]<child[v]) son[u]=v;
    }
    if(num[u]>rt[u]) check=false;
    if(num[u]<lt[u]) b[u]=lt[u]-num[u],num[u]=lt[u];
    rt[u]-=num[u];
}

void solve(){
    cin >> n;
    reset();
    for(int i=2;i<=n;i++){
        cin >> p[i];
        edge[p[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) cin >> c[i];
    for(int i=1;i<=n;i++) cin >> lt[i] >> rt[i];
    dfs(1);
    if(!check){
        cout << -1 << '\n';
        return;
    }
    hld_dfs(1,0);
    Segtree::build(1,n,1);
    Segtree2::build(1,n,1);
    dfs_cal(1);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=b[i]*c[i];
    cout << ans << '\n';
    for(int i=1;i<=n;i++) cout << b[i] << ' ';
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();

}
