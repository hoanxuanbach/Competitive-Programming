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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=1e9+7;
const int maxn=500005;
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
int n,q,a[maxn],ans[maxn];
vector<pii> que[maxn];
struct node{
    int Max,res,lazy=-inf;
    node(){};
    friend node operator+(node a,node b){
        node cur;
        cur.Max=max(a.Max,b.Max);
        cur.res=max(a.res,b.res);
        return cur;
    }
};
namespace Segtree{
    node tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id].res=-inf;
            tree[id].Max=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void getnew(int id,int val){
        tree[id].lazy=max(tree[id].lazy,val);
        tree[id].res=max(tree[id].res,tree[id].lazy+tree[id].Max);
    }
    void pushdown(int id){
        if(tree[id].lazy==-inf) return;
        getnew(id<<1,tree[id].lazy);
        getnew(id<<1|1,tree[id].lazy);
        tree[id].lazy=-inf;
    }
    void update(int l,int r,int id,int p,int val){
        if(p<=l){getnew(id,val);return;}
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        update(mid+1,r,id<<1|1,p,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    int query(int l,int r,int id,int p){
        if(l==r) return tree[id].res;
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return max(tree[id<<1].res,query(mid+1,r,id<<1|1,p));
    }
}
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        que[l].push_back({r,i});
    }
    vector<int> v;
    Segtree::build(1,n,1);
    for(int i=n;i>=1;i--){
        while(!v.empty() && a[i]>=a[v.back()]){
            int p=v.back();v.pop_back();
            if(2*p-i<=n) Segtree::update(1,n,1,2*p-i,a[i]+a[p]);
        }
        if(!v.empty()){
            int p=v.back();
            if(2*p-i<=n) Segtree::update(1,n,1,2*p-i,a[i]+a[p]);
        }
        v.push_back(i);
        for(auto &[r,id]:que[i]) ans[id]=Segtree::query(1,n,1,r);
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
