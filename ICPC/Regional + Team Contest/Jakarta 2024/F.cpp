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
const int base=101;

struct node{
    int sum=0,Max=-inf,pre=0,suf=0;
    node(int a=0):Max(a),sum(a),pre(a),suf(a){}
    friend node operator+(node a,node b){
        node res;
        res.Max=max({a.Max,b.Max,a.suf+b.pre});
        res.sum=a.sum+b.sum;
        res.pre=max(a.pre,a.sum+b.pre);
        res.suf=max(b.suf,b.sum+a.suf);
        return res;
    }
};

int cur[maxn];
namespace Segtree{
    node tree[4*maxn];
    void update(int l,int r,int id,int p){
        if(l==r){
            tree[id]=node(cur[l]);
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node query(int l,int r,int id,int tl,int tr){
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        if(tr<=mid) return query(l,mid,id<<1,tl,tr);
        else if(mid<tl) return query(mid+1,r,id<<1|1,tl,tr);
        else return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}

int n,m,q,res[maxn];
vector<pii> pos[maxn];
vector<piii> query[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int l,r,x;cin >> l >> r >> x;
        pos[l].push_back({i,x});
        pos[r+1].push_back({i,-x});
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int k,s,t;cin >> k >> s >> t;
        query[k].push_back({{s,t},i});
    }
    for(int i=1;i<=n;i++){
        for(auto [id,val]:pos[i]){
            cur[id]+=val;
            Segtree::update(1,m,1,id);
        }
        for(auto [p,id]:query[i]) res[id]=Segtree::query(1,m,1,p.fi,p.se).Max;
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
