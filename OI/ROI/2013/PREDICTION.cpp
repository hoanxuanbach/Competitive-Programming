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
const int maxl=20;
const int maxa=500000;
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

namespace Segtree{
    int tree[4*maxn],sum[4*maxn],lazy[4*maxn];
    void getnew(int id,int l,int r,int val){
        lazy[id]+=val;
        tree[id]+=val*(r-l+1)*(r-l+2)/2;
        sum[id]+=val*(r-l+1);
    }
    void pushdown(int id,int l,int r){
        if(lazy[id]==0) return;
        int mid=(l+r)>>1;
        getnew(id<<1,l,mid,lazy[id]);
        getnew(id<<1|1,mid+1,r,lazy[id]);
        lazy[id]=0;
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,l,r,val);
            return;
        }
        pushdown(id,l,r);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+sum[id<<1]*(r-mid)+tree[id<<1|1];
        sum[id]=sum[id<<1]+sum[id<<1|1];
    }
    piii query_val(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {{0,0},0};
        if(tl<=l && r<=tr) return {{tree[id],sum[id]},r-l+1};
        pushdown(id,l,r);
        int mid=(l+r)>>1;
        piii x=query_val(l,mid,id<<1,tl,tr),y=query_val(mid+1,r,id<<1|1,tl,tr);
        return {{x.fi.fi+x.fi.se*y.se+y.fi.fi,x.fi.se+y.fi.se},x.se+y.se};
    }
    int query_sum(int l,int r,int id,int p){
        if(l==r) return sum[id];
        pushdown(id,l,r);
        int mid=(l+r)>>1;
        if(p<=mid) return query_sum(l,mid,id<<1,p);
        else return sum[id<<1]+query_sum(mid+1,r,id<<1|1,p);
    }
}
int n,k;
vector<int> pos[maxn];

void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        pos[x].push_back(i);
    }
    int ans=0;
    for(int i=1;i<=k;i++){
        if(pos[i].empty()) continue;
        int sz=(int)pos[i].size(),d=0,p=0;
        pos[i].push_back(n+1);
        int aa=n-sz+1;
        for(int x:pos[i]){
            int k=x-p;//(d-k+1->d)
            ans+=Segtree::query_val(1,n+1,1,d-k+aa,d-1+aa).fi.fi;
            if(d-k-1+aa) ans+=Segtree::query_sum(1,n+1,1,d-k-1+aa)*k;
            Segtree::update(1,n+1,1,d-k+1+aa,d+aa,1);
            p=x;d+=2-k;
        }
        d=0;p=0;
        for(int x:pos[i]){
            int k=x-p;
            Segtree::update(1,n+1,1,d-k+1+aa,d+aa,-1);
            p=x;d+=2-k;
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
