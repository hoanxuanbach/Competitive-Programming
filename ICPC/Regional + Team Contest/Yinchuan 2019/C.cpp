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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int maxn=1000005;

struct node{
    int lazy=0,Min_all=inf,Min_dp=inf,Min_dep=2*inf;
    node(){}
};

namespace Segtree{
    node tree[4*maxn];
    inline void getnew(int id,int val){
        tree[id].lazy+=val;
        tree[id].Min_dep-=val;
        tree[id].Min_all+=val;
    }
    inline void pushdown(int id){
        if(tree[id].lazy==0) return;
        getnew(id<<1,tree[id].lazy);
        getnew(id<<1|1,tree[id].lazy);
        tree[id].lazy=0;
    }
    inline void update(int l,int r,int id,int tl,int tr,int val){
        //cout << "update " << l << ' ' << r << ' ' << id << endl;
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            if(tree[id].Min_dep>=val){
                getnew(id,val);
                return;
            }
        }
        if(l==r){
            tree[id].Min_all=tree[id].Min_dp+val-tree[id].Min_dep;
            tree[id].Min_dep=tree[id].Min_dp=inf;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id].Min_all=min(tree[id<<1].Min_all,tree[id<<1|1].Min_all);
        tree[id].Min_dep=min(tree[id<<1].Min_dep,tree[id<<1|1].Min_dep);
        tree[id].Min_dp=min(tree[id<<1].Min_dp,tree[id<<1|1].Min_dp);
    }
    inline void update_dp(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id].Min_dp=tree[id].Min_dep=val;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) update_dp(l,mid,id<<1,p,val);
        else update_dp(mid+1,r,id<<1|1,p,val);
        tree[id].Min_dp=min(tree[id<<1].Min_dp,tree[id<<1|1].Min_dp);
        tree[id].Min_dep=min(tree[id<<1].Min_dep,tree[id<<1|1].Min_dep);
    }
    inline int query(int l,int r,int id,int p){
        if(l==r) return min(tree[id].Min_all,tree[id].Min_dp);
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return min({tree[id<<1].Min_all,tree[id<<1].Min_dp,query(mid+1,r,id<<1|1,p)});
    }
}

int n,k,dp[maxn],x[maxn],Min[maxn],Max[maxn],sz_Min,sz_Max;

void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> x[i];
    for(int i=1;i<=n;i++){
        x[i]^=dp[i-1];
        //cout << x[i] << '\n';
        while(sz_Min && x[Min[sz_Min]]>x[i]){
            int r=Min[sz_Min]-1;sz_Min--;
            int l=(sz_Min?Min[sz_Min]:1);
            //cout << "Min " << l << ' ' << r << ' ' << x[r+1]-x[i] << '\n';
            if(l<=r) Segtree::update(1,n,1,l,r,x[r+1]-x[i]);
        }
        while(sz_Max && x[Max[sz_Max]]<x[i]){
            int r=Max[sz_Max]-1;sz_Max--;
            int l=(sz_Max?Max[sz_Max]:1);
            if(l<=r) Segtree::update(1,n,1,l,r,x[i]-x[r+1]);
        }
        Min[++sz_Min]=Max[++sz_Max]=i;
        if(i<k) dp[i]=0;
        else{
            dp[i]=x[Max[1]]-x[Min[1]];
            if(i>=2*k) dp[i]=min(dp[i],Segtree::query(1,n,1,i-k));
            Segtree::update_dp(1,n,1,i,dp[i]);
        }
        cout << dp[i] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}