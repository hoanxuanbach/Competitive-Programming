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

int n,q,a[maxn],c[maxn];

namespace Segtree{
    int tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    void update(int l,int r,int id,int p){
        if(l==r){
            tree[id]=a[p];
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    int query_lt(int l,int r,int id,int p,int val){
        if(p<1) return 0;
        if(r<=p && tree[id]<=val) return 0;
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(p<=mid) return query_lt(l,mid,id<<1,p,val);
        else{
            int x=query_lt(mid+1,r,id<<1|1,p,val);
            if(x) return x;
            else return query_lt(l,mid,id<<1,p,val);
        }
    }
    int query_rt(int l,int r,int id,int p,int val){
        //cout << "query_rt " << l << ' ' << r << ' ' << id << ' ' << p << '\n';
        if(p>n) return n+1;
        if(p<=l && tree[id]<=val) return n+1;
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(p<=mid){
            int x=query_rt(l,mid,id<<1,p,val);
            if(x!=n+1) return x;
            else return query_rt(mid+1,r,id<<1|1,p,val);
        }
        else return query_rt(mid+1,r,id<<1|1,p,val);
    }
}

pair<char,int> qq[maxn];
int ans[maxn];

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i],c[i]=a[i];
    Segtree::build(1,n,1);
    int res=0;
    for(int i=1;i<=n;i++){
        int lt=Segtree::query_lt(1,n,1,i-1,a[i]);
        int rt=Segtree::query_rt(1,n,1,i+1,a[i]-1);
        res+=(i-lt)*(rt-i)*a[i];
    }
    //cout << res << '\n';
    for(int i=1;i<=q;i++){
        char c;cin >> c;
        int p;cin >> p;
        qq[i]={c,p};
        if(c=='+'){
            int lt=Segtree::query_lt(1,n,1,p-1,a[p]);
            int rt=Segtree::query_rt(1,n,1,p+1,a[p]);
            //cout << p << ' ' << a[p] << ' ' << lt << ' ' << rt << '\n';
            res+=(p-lt)*(rt-p);a[p]++;
            Segtree::update(1,n,1,p);
        }
        else{
            a[p]--;
            int lt=Segtree::query_lt(1,n,1,p-1,a[p]);
            int rt=Segtree::query_rt(1,n,1,p+1,a[p]);
            res-=(p-lt)*(rt-p);
            Segtree::update(1,n,1,p);
        }
        ans[i]+=res;
    }

    for(int i=1;i<=n;i++) a[i]=-c[i];
    Segtree::build(1,n,1);
    res=0;
    for(int i=1;i<=n;i++){
        int lt=Segtree::query_lt(1,n,1,i-1,a[i]);
        int rt=Segtree::query_rt(1,n,1,i+1,a[i]-1);
        res+=(i-lt)*(rt-i)*a[i];
    }
    for(int i=1;i<=q;i++){
        char c=qq[i].fi;
        int p=qq[i].se;
        if(c=='-'){
            int lt=Segtree::query_lt(1,n,1,p-1,a[p]);
            int rt=Segtree::query_rt(1,n,1,p+1,a[p]);
            res+=(p-lt)*(rt-p);a[p]++;
            Segtree::update(1,n,1,p);
        }
        else{
            a[p]--;
            int lt=Segtree::query_lt(1,n,1,p-1,a[p]);
            int rt=Segtree::query_rt(1,n,1,p+1,a[p]);
            res-=(p-lt)*(rt-p);
            Segtree::update(1,n,1,p);
        }
        ans[i]+=res;
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
