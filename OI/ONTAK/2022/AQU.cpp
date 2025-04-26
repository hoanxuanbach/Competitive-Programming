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
const int mod=998244353;
const int inf=1e18;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}
int n,q,a[maxn];

struct node{
    int sum=0,val=0,cmin=0,min1=inf,min2=inf,lazy=0,mul=1,tl=0;
    node(){}
    friend node operator+(node a,node b){
        node res;
        res.sum=(a.sum+b.sum)%mod;
        res.min1=min(a.min1,b.min1);
        if(a.min1==res.min1){
            res.cmin+=a.cmin;
            res.val=a.val;
        }
        if(b.min1==res.min1){
            res.cmin+=b.cmin;
            res.val=b.val;
        }
        res.min2=min(a.min2,b.min2);
        if(a.min1!=b.min1) res.min2=min(res.min2,max(a.min1,b.min1));
        return res;
    }
};

namespace Segtree{
    node T[4*maxn];
    void build(int l,int r,int id){
        T[id].mul=1;T[id].lazy=0;
        if(l==r){
            T[id].val=T[id].sum=power(base,a[l]);
            T[id].min1=a[l];T[id].cmin=1;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        T[id]=T[id<<1]+T[id<<1|1];
        //cout << "build " << l << ' ' << r << ' ' << id << ' ' << T[id].min1 << '\n';
    }
    void push_min(int l,int r,int id,int k,int x){
        if(T[id].min1>=k) return;
        T[id].sum=(T[id].sum-T[id].val*T[id].cmin%mod+mod)%mod;
        T[id].min1=k;
        T[id].val=x;
        T[id].sum=(T[id].sum+T[id].val*T[id].cmin%mod)%mod;
        if(!T[id].tl) T[id].tl=2;
    }
    void push_full(int l,int r,int id,int k,int x){
        T[id].tl=1;
        T[id].lazy=0;
        T[id].mul=1;
        T[id].min1=k;
        T[id].min2=inf;
        T[id].cmin=r-l+1;
        T[id].val=x;
        T[id].sum=x*(r-l+1)%mod;
    }
    void push_add(int l,int r,int id,int k,int x){
        T[id].lazy+=k;
        T[id].mul=T[id].mul*x%mod;
        T[id].min1+=k;
        T[id].min2+=k;
        T[id].sum=T[id].sum*x%mod;
        T[id].val=T[id].val*x%mod;
    }
    void pushdown(int l,int r,int id){
        int mid=(l+r)>>1;
        if(T[id].lazy){
            push_add(l,mid,id<<1,T[id].lazy,T[id].mul);
            push_add(mid+1,r,id<<1|1,T[id].lazy,T[id].mul);
            T[id].lazy=0;T[id].mul=1;
        }
        if(T[id].tl==1){
            push_full(l,mid,id<<1,T[id].min1,T[id].val);
            push_full(mid+1,r,id<<1|1,T[id].min1,T[id].val);
        }
        else if(T[id].tl==2){
            push_min(l,mid,id<<1,T[id].min1,T[id].val);
            push_min(mid+1,r,id<<1|1,T[id].min1,T[id].val);
        }
        T[id].tl=0;
    }
    int query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0;
        if(tl<=l && r<=tr){
            //cout << "query " << l << ' ' << r << ' ' << T[id].sum << ' ' << T[id].min1 << '\n';
            return T[id].sum;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        return (query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr))%mod;
    }
    void update1(int l,int r,int id,int tl,int tr,int k,int x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            push_full(l,r,id,k,x);
            return;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        update1(l,mid,id<<1,tl,tr,k,x);update1(mid+1,r,id<<1|1,tl,tr,k,x);
        T[id]=T[id<<1]+T[id<<1|1];
    }
    void update2(int l,int r,int id,int tl,int tr,int k,int x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            push_add(l,r,id,k,x);
            //cout << "update2 " << l << ' ' << r << ' ' << id << ' ' << T[id].min1 << '\n';
            return;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        update2(l,mid,id<<1,tl,tr,k,x);update2(mid+1,r,id<<1|1,tl,tr,k,x);
        T[id]=T[id<<1]+T[id<<1|1];
        //cout << "update2 " << l << ' ' << r << ' ' << id << ' ' << T[id].min1 << '\n';
    }
    void update3(int l,int r,int id,int tl,int tr,int k,int x){
        if(tr<l || r<tl || T[id].min1>=k) return;
        if(tl<=l && r<=tr && k<T[id].min2){
            //cout << '*' << l << ' ' << r << ' ' << id << '\n';
            push_min(l,r,id,k,x);
            //cout << "update3 " << l << ' ' << r << ' ' << id << ' ' << T[id].min1 << '\n';
            return;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        update3(l,mid,id<<1,tl,tr,k,x);update3(mid+1,r,id<<1|1,tl,tr,k,x);
        T[id]=T[id<<1]+T[id<<1|1];
        //cout << "update3 " << l << ' ' << r << ' ' << id << ' ' << T[id].min1 << '\n';
    }
}

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    Segtree::build(1,n,1);
    //cout << '\n';
    for(int i=1;i<=q;i++){
        int id,l,r,k;cin >> id;
        if(id==0){
            int a1,b1,a2,b2;cin >> a1 >> b1 >> a2 >> b2;
            int d1=Segtree::query(1,n,1,a1,b1);
            int d2=Segtree::query(1,n,1,a2,b2);
            //cout << d1 << ' ' << d2 << '\n';
            if(b1-a1==b2-a2 && d1==d2) cout << "YES\n";
            else cout << "NO\n";
        }
        else{
            cin >> l >> r >> k;
            int x=power(base,k);
            if(id==1) Segtree::update1(1,n,1,l,r,k,x);
            else if(id==2) Segtree::update2(1,n,1,l,r,k,x);
            else Segtree::update3(1,n,1,l,r,k,x);
        }
        //cout << '\n';
    }
}

signed main(){
    //freopen("AQU.INP","r",stdin);
    //freopen("AQU.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
