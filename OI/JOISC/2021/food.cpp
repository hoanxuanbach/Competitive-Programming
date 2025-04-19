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
const int maxn=250005;
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
int n,m,q,c[maxn],ans[maxn],lst;
vector<tuple<int,int,int>> add[maxn];
namespace Segtree{
    int tree[4*maxn],lazy[4*maxn],sum[4*maxn];
    void getnew(int id,int val){
        tree[id]+=val;
        lazy[id]+=val;
    }
    void pushdown(int id){
        if(lazy[id]==0) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    void update(int l,int r,int id,int p,int k){
        if(l==r){getnew(id,k);return;}
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid){update(l,mid,id<<1,p,k);getnew(id<<1|1,k);}
        else update(mid+1,r,id<<1|1,p,k);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    void updatesum(int l,int r,int id,int p,int k){
        if(l==r){sum[id]+=k;return;}
        int mid=(l+r)>>1;
        if(p<=mid) updatesum(l,mid,id<<1,p,k);
        else updatesum(mid+1,r,id<<1|1,p,k);
        sum[id]=sum[id<<1]+sum[id<<1|1];
    }
    int queryMin(int l,int r,int id,int p){
        if(l==r) return lst=tree[id];
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) return queryMin(l,mid,id<<1,p);
        else return min(tree[id<<1],queryMin(mid+1,r,id<<1|1,p));
    }
    pii query(int l,int r,int id,int p,int cnt){
        if(l==r) return {sum[id],l};
        pushdown(id);
        int mid=(l+r)>>1;
        if(r<p){
            if(sum[id<<1|1]>=cnt) return query(mid+1,r,id<<1|1,p,cnt);
            else{
                pii f=query(l,mid,id<<1,p,cnt-sum[id<<1|1]);
                return {f.fi+sum[id<<1|1],f.se};
            }
        }
        else if(p<=mid) return query(l,mid,id<<1,p,cnt);
        else{
            pii f=query(mid+1,r,id<<1|1,p,cnt);
            if(f.fi>=cnt) return f;
            else if(f.fi+sum[id<<1]<cnt) return {f.fi+sum[id<<1],-1};
            else{
                pii g=query(l,mid,id<<1,p,cnt-f.fi);
                return {f.fi+g.fi,g.se};
            }
        }
    }
}
void solve(){
    cin >> n >> m >> q;
    for(int i=1;i<=q;i++){
        int t,l,r,k;cin >> t;ans[i]=-1;
        if(t==1) cin >> l >> r >> c[i] >> k;
        else if(t==2) cin >> l >> r >> k,k=-k;
        else cin >> l >> k;
        if(t==3) add[l].push_back({t,i,k});
        else{
            add[l].push_back({t,i,k});
            add[r+1].push_back({t,i,-k});
        }
    }
    for(int i=1;i<=n;i++){
        for(auto &[t,id,k]:add[i]){
            if(t<=2) Segtree::update(1,q,1,id,k);
            if(t==1) Segtree::updatesum(1,q,1,id,k);
            if(t==3){
                int Min=min(0LL,Segtree::queryMin(1,q,1,id));lst-=Min;
                //if(id==6) cout << id << ' ' << lst << ' ' << k << ' ' << Segtree::query(1,q,1,id,lst-k+1).se << '\n';
                if(k>lst) ans[id]=0;
                else ans[id]=c[Segtree::query(1,q,1,id,lst-k+1).se];
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(ans[i]!=-1) cout << ans[i] << '\n';
    }
}
/*
1457 236823 6
1 282 1270 166817 1
2 258 413 1
3 71 1
1 599 1196 220672 1
1 603 1271 178260 1
3 976 3
*/
signed main(){
    //freopen("food.inp","r",stdin);
    //freopen("food.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

