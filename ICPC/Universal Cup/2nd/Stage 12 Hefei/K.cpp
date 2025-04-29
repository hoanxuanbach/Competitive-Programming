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
const int maxn=500005;
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

int n,a[maxn],ca[maxn],g[maxn],f[maxn];
vector<int> edge[maxn],com;
int sz;

int child[maxn],son[maxn];
void pre_dfs(int u,int p){
    child[u]=1;
    for(int v:edge[u]){
        if(v==p) continue;
        pre_dfs(v,u);child[u]+=child[v];
        if(child[son[u]]<child[v]) son[u]=v;
    }
}

namespace Segtree{
    int all=0;
    struct node{
        int val[2]={-inf,-inf};
        node(){}
        friend node operator+(node a,node b){
            node res;
            for(int i=0;i<=1;i++) res.val[i]=max(a.val[i],b.val[i]);
            return res;
        }
    }tree[4*maxn];
    int query(int l,int r,int id,int tl,int tr,int t){
        if(tr<l || r<tl || tr<tl) return -inf;
        if(tl<=l && r<=tr) return tree[id].val[t]+all;
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr,t),query(mid+1,r,id<<1|1,tl,tr,t));
    }
    void change(int l,int r,int id,int p,int val){
        if(l==r){
            if(val==-inf) tree[id].val[0]=tree[id].val[1]=-inf;
            else{
                tree[id].val[0]=max(tree[id].val[0],val-all);
                tree[id].val[1]=max(tree[id].val[1],val-all+com[l-1]);
            }
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) change(l,mid,id<<1,p,val);
        else change(mid+1,r,id<<1|1,p,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
}

vector<pii> ver;
void cal(int u,int p){
    if(f[u]!=-inf) ver.push_back({f[u],ca[u]});
    for(int v:edge[u]) if(v!=p) cal(v,u);
}

void del(int u,int p){
    f[u]=Segtree::query(1,sz,1,ca[u],ca[u],0);
    if(f[u]!=-inf) Segtree::change(1,sz,1,ca[u],-inf);
    for(int v:edge[u]) if(v!=p) del(v,u);
}

int dfs(int u,int p,int t){
    int total=0;
    for(int v:edge[u]) if(v!=p && v!=son[u]) total+=dfs(v,u,1);
    if(son[u]){
        total+=dfs(son[u],u,0);
        Segtree::all+=total-g[son[u]];
    }
    int Max=total;
    for(int v:edge[u]){
        if(v==p || v==son[u]) continue;
        ver.clear();cal(v,u);
        for(pii x:ver) Max=max(Max,x.fi-g[v]+max(Segtree::query(1,sz,1,1,x.se,1),Segtree::query(1,sz,1,x.se+1,sz,0)+com[x.se-1]));
        for(pii x:ver) Segtree::change(1,sz,1,x.se,x.fi+total-g[v]);
    }
    Max=max(Max,max(Segtree::query(1,sz,1,1,ca[u],1),Segtree::query(1,sz,1,ca[u]+1,sz,0)+a[u]));
    Segtree::change(1,sz,1,ca[u],total);
    if(t){
        del(u,p);
        Segtree::all=0;
    }
    //cout << '*' << u << ' ' << Max << '\n';
    return g[u]=Max;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        com.push_back(a[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=1;i<=n;i++) ca[i]=lower_bound(com.begin(),com.end(),a[i])-com.begin()+1;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    pre_dfs(1,0);
    cout << dfs(1,0,0) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
