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
const int mod2=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=100000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
namespace Segtree{
    int tree[4*maxn],num[4*maxn];
    void update(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]+=val;
            num[id]+=p*val;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        num[id]=num[id<<1]+num[id<<1|1];
    }
    int query(int l,int r,int id,int lim){
        if(l==r) return lim*l;
        int mid=(l+r)>>1;
        if(lim<=tree[id<<1]) return query(l,mid,id<<1,lim);
        else return num[id<<1]+query(mid+1,r,id<<1|1,lim-tree[id<<1]);
    }
}
struct que{int g,L,id;};
int n,m,ans[maxn];
vector<pii> a[maxn];
vector<que> query[maxn];
void dnc(int l,int r){
    int mid=(l+r)>>1,mid1=(l+mid-1)>>1,mid2=(mid+1+r)>>1;
    for(auto x:query[mid]){
        if(x.L<=Segtree::tree[1] && Segtree::query(1,maxa,1,x.L)<=x.g){
            ans[x.id]=mid;
            if(mid<r) query[mid2].push_back(x);
        }
        else if(l<mid) query[mid1].push_back(x);
    }
    if(l<mid){
        for(int i=mid1;i<mid;i++){
            for(pii x:a[i]) Segtree::update(1,maxa,1,x.fi,x.se);
        }
        dnc(l,mid-1);
        for(int i=mid1;i<mid;i++){
            for(pii x:a[i]) Segtree::update(1,maxa,1,x.fi,-x.se);
        }
    }
    if(mid<r){
        for(int i=mid;i<mid2;i++){
            for(pii x:a[i]) Segtree::update(1,maxa,1,x.fi,-x.se);
        }
        dnc(mid+1,r);
        for(int i=mid;i<mid2;i++){
            for(pii x:a[i]) Segtree::update(1,maxa,1,x.fi,x.se);
        }
    }
}
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int d,p,l;cin >> d >> p >> l;
        a[d].push_back({p,l});
    }
    for(int i=1;i<=m;i++){
        int g,L;cin >> g >> L;ans[i]=-1;
        query[maxa/2].push_back({g,L,i});
    }
    for(int i=maxa/2;i<=maxa;i++){
        for(pii x:a[i]) Segtree::update(1,maxa,1,x.fi,x.se);
    }
    dnc(1,maxa);
    for(int i=1;i<=m;i++) cout << ans[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
