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
const int maxn=300005;
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
struct node{
    int l,r,cost,nxt;
    node(int _l=-inf,int _r=inf,int _cost=0,int _nxt=inf):l(_l),r(_r),cost(_cost),nxt(_nxt){}
    friend node operator+(node a,node b){
        node res;
        if(a.nxt!=inf) res=node(a.l,a.r,a.cost+max(a.nxt-b.r,0LL),max(min(a.nxt,b.r),b.l));
        else if(a.r<b.l) res=node(a.r,a.r,0,b.l);
        else if(a.l>b.r) res=node(a.l,a.l,a.l-b.r,b.r);
        else if(b.nxt!=inf) return b;
        else res=node(max(a.l,b.l),min(a.r,b.r),0,inf);
        if(b.nxt!=inf) res.nxt=b.nxt,res.cost+=b.cost;
        return res;
    }
};
struct Segtree{
    node tree[4*maxn];
    void update(int l,int r,int id,int p,int lt,int rt){
        if(l==r) return tree[id]=node(lt-p,rt-p-1,0,inf),void();
        int mid=(l+r)/2;
        if(p<=mid) update(l,mid,id<<1,p,lt,rt);
        else update(mid+1,r,id<<1|1,p,lt,rt);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node query(int l,int r,int id,int tl,int tr){
        if(l>tr||tl>r) return node();
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)/2;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}s[2];
int n,q;
void update(int p,int l,int r){
    s[0].update(1,n-1,1,p,l,r);
    s[1].update(1,n-1,1,n-p,l,r);
}
void solve(){
    cin >> n >> q;
    for(int i=1;i<n;i++){int l,r;cin >> l >> r;update(i,l,r);}
    for(int i=1;i<=q;i++){
        int t,a,b,c,d;cin >> t;
        if(t==1){
            cin >> a >> c >> d;
            update(a,c,d);
        }
        else{
            cin >> a >> b >> c >> d;
            if(a==c) cout << max(b-d,0LL) << '\n';
            else{
                int rt=0;
                if(a>c) rt=1,a=n-a+1,c=n-c+1;
                node res=node(b-a,b-a,0,inf)+s[rt].query(1,n-1,1,a,c-1)+node(d-c,d-c,0,inf);
                cout << res.cost << '\n';
            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
