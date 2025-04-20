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
int k,a[maxn];
namespace Segtree{
    int Max[4*maxn],sum[4*maxn];
    void build(int l,int r,int id){
        if(l==r){Max[id]=sum[id]=a[l];return;}
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        Max[id]=max(Max[id<<1],Max[id<<1|1]);
        sum[id]=sum[id<<1]+sum[id<<1|1];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl || k==-val) return;
        if(tl<=l && r<=tr && Max[id]==0 && val==-1) return;
        if(l==r){
            sum[id]=Max[id]=(val==-1?sum[id]/k:val);
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        Max[id]=max(Max[id<<1],Max[id<<1|1]);
        sum[id]=sum[id<<1]+sum[id<<1|1];
    }
    int query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0;
        if(tl<=l && r<=tr) return sum[id];
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}
void solve(){
    int n,q;cin >> n >> q >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    Segtree::build(1,n,1);
    for(int i=1;i<=q;i++){
        int t,x,y;cin >> t >> x >> y;
        if(t==1) Segtree::update(1,n,1,x,x,y);
        else if(t==2) Segtree::update(1,n,1,x,y,-1);
        else cout << Segtree::query(1,n,1,x,y) << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
