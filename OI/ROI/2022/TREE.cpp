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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,a[maxn],p[maxn],l[maxn],r[maxn];
vector<pii> query[maxn];

int q,yy[maxn],xx[maxn];

struct Segtree1{
    int tree[4*maxn];
    void update(int l,int r,int id,int p){
        if(l==r){
            tree[id]++;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    int query(int l,int r,int id,int val){
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(tree[id<<1]<val) return query(mid+1,r,id<<1|1,val-tree[id<<1]);
        else return query(l,mid,id<<1,val);
    }
}ST;

struct Segtree_Min{
    int tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    int query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return inf;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
}SMin;

struct BIT{
    int bit[maxn];
    void update(int x){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}Bit;

vector<int> query2[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],p[a[i]]=i;
    cin >> q;
    for(int i=1;i<=q;i++){
        int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
        xx[i]=min(x1,x2);
        query[x1].push_back({y1,i});
        query[x2].push_back({y2,-i});
    }
    for(int i=1;i<=n;i++){
        ST.update(1,n,1,p[i]);
        for(pii x:query[i]){
            int d=i-x.fi,pos=0;
            if(d!=0) pos=ST.query(1,n,1,d);
            if(x.se>0) l[x.se]=pos;
            else r[-x.se]=pos;
        }
    }
    SMin.build(1,n,1);
    for(int i=1;i<=q;i++){
        if(l[i]>r[i]) swap(l[i],r[i]);
        if(l[i]<r[i]) xx[i]=min(xx[i],SMin.query(1,n,1,l[i]+1,r[i])-1);
        query2[l[i]].push_back(i);
        //cout << l[i] << ' ' << r[i] << '\n';
    }
    for(int i=0;i<=n;i++){
        if(i) Bit.update(a[i]);
        for(int id:query2[i]) yy[id]=xx[id]-Bit.query(xx[id]);
    }
    for(int i=1;i<=q;i++) cout << xx[i] << ' ' << yy[i] << '\n';
}

signed main(){
    freopen("TREE.INP","r",stdin);
    freopen("TREE.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
