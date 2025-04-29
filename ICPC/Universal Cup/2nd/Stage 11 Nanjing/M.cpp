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
const int maxn=100005;
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

int n,q,total;
pii Max;

struct Segtree{
    int sum[4*maxn],Max[4*maxn],lazy[4*maxn];
    void build(int l,int r,int id,vector<int> &x){
        lazy[id]=0;
        if(l==r){
            sum[id]=x[l];
            Max[id]=x[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1,x);build(mid+1,r,id<<1|1,x);
        sum[id]=sum[id<<1]+sum[id<<1|1];
        Max[id]=max(Max[id<<1],Max[id<<1|1]);
    }
    void getnew(int l,int r,int id,int val){
        Max[id]=lazy[id]=val;
        sum[id]=(r-l+1)*val;
    }
    void pushdown(int l,int r,int id){
        if(!lazy[id]) return;
        int mid=(l+r)>>1;
        getnew(l,mid,id<<1,lazy[id]);
        getnew(mid+1,r,id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    int query_pos(int l,int r,int id,int p,int val){
        if(l==r){
            if(Max[id]<val) return l;
            else return l-1;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        if(p<=mid){
            if(val<=Max[id<<1]) return query_pos(l,mid,id<<1,p,val);
            else return query_pos(mid+1,r,id<<1|1,p,val);
        }
        else return query_pos(mid+1,r,id<<1|1,p,val);
    }
    int query(int l,int r,int id,int p){
        if(l==r) return sum[id];
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return sum[id<<1]+query(mid+1,r,id<<1|1,p);
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(l,r,id,val);
            return;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        sum[id]=sum[id<<1]+sum[id<<1|1];
        Max[id]=max(Max[id<<1],Max[id<<1|1]);
    }
    void build(vector<int> x){
        for(int i=1;i<=n;i++){
            x[i]=max(x[i],x[i-1]);
            //cout << x[i] << ' ';
        }
        //cout << '\n';
        build(1,n,1,x);
    }
    void update(int x,int val){
        int pos=query_pos(1,n,1,x,val);
        //cout << "update " << x << ' ' << pos << ' ' << val << '\n';
        if(x<=pos) update(1,n,1,x,pos,val);
    }
    int query(int x){
        //cout << "query " << x << ' ' << query(1,n,1,x) << '\n';
        return query(1,n,1,x);
    }
}pre,suf;

void solve(){
    cin >> n;
    vector<int> a(n+1,0);
    total=0;Max={0,0};
    for(int i=1;i<=n;i++){
        cin >> a[i],total+=a[i];
        Max=max(Max,{a[i],i});
    }
    pre.build(a);
    reverse(a.begin()+1,a.end());
    suf.build(a);
    reverse(a.begin()+1,a.end());
    cin >> q;
    for(int i=1;i<=q;i++){
        int x,v;cin >> x >> v;
        total+=v;a[x]+=v;
        Max=max(Max,{a[x],x});
        pre.update(x,a[x]);
        suf.update(n-x+1,a[x]);
        int d=pre.query(Max.se);
        if(Max.se<n) d+=suf.query(n-Max.se);
        cout << d-total << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
