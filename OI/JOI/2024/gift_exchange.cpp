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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,A[maxn],B[maxn],q,c[maxn];
vector<pii> qq[maxn];

namespace Segtree{
    int tree[8*maxn],lazy[8*maxn];
    void init(){
        for(int i=1;i<=8*n;i++) tree[i]=lazy[i]=0;
    }
    void pushdown(int id){
        if(!lazy[id]) return;
        int val=lazy[id];
        lazy[id<<1]=max(lazy[id<<1],val);
        tree[id<<1]=max(tree[id<<1],val);
        lazy[id<<1|1]=max(lazy[id<<1|1],val);
        tree[id<<1|1]=max(tree[id<<1|1],val);
        lazy[id]=0;
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            lazy[id]=max(lazy[id],val);
            tree[id]=max(tree[id],val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    int query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0;
        if(tl<=l && r<=tr) return tree[id];
        pushdown(id);
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
}

namespace BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    void update_range(int l,int r,int val){
        update(l,val);
        update(r+1,-val);
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}


vector<int> cal(){
    vector<int> lt(n+1,0);
    Segtree::init();
    for(int i=1;i<=n;i++){
        lt[i]=Segtree::query(1,2*n,1,B[i],A[i])+1;
        Segtree::update(1,2*n,1,B[i],A[i],i);
    }
    return lt;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> A[i];
    for(int i=1;i<=n;i++) cin >> B[i];
    vector<int> lt=cal();
    reverse(A+1,A+n+1);
    reverse(B+1,B+n+1);
    vector<int> rt=cal();
    reverse(rt.begin()+1,rt.end());
    for(int i=1;i<=n;i++) rt[i]=n+1-rt[i];

    for(int i=1;i<=n;i++) qq[rt[i]+1].push_back({lt[i],-i});
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        qq[r].push_back({l,i});
    }
    for(int i=1;i<=n;i++){
        BIT::update_range(lt[i],i,1);
        for(auto [l,id]:qq[i]){
            if(id<0) BIT::update_range(l,-id,-1);
            else c[id]=BIT::query(l);
        }
    }
    for(int i=1;i<=q;i++) cout << (c[i]?"No":"Yes") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
