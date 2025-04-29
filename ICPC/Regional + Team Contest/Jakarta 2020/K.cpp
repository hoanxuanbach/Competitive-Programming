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
const int mod=1e9+7;
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

struct matrix{
    int x[2][2],n=2,m=2;
    matrix(int n=2,int m=2):n(n),m(m){
        memset(x,0,sizeof(x));
    }
    friend matrix operator*(matrix a,matrix b){
        matrix res(a.n,b.m);
        for(int i=0;i<a.n;i++) for(int j=0;j<b.m;j++){
            for(int k=0;k<a.m;k++) res.x[i][j]=(res.x[i][j]+a.x[i][k]*b.x[k][j])%mod;
        }
        return res;
    }
};

int n,q;
char c[maxn];
matrix cur(1,2);

namespace Segtree{
    int lazy[4*maxn];
    matrix tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id].x[0][0]=tree[id].x[1][1]=1;
            if(c[l]=='A') tree[id].x[1][0]=1;
            else tree[id].x[0][1]=1;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]*tree[id<<1|1];
    }
    void getnew(int id){
        lazy[id]^=1;
        for(int i=0;i<=1;i++) swap(tree[id].x[0][i],tree[id].x[1][i^1]);
    }
    void pushdown(int id){
        if(!lazy[id]) return;
        getnew(id<<1);
        getnew(id<<1|1);
        lazy[id]=0;
    }
    void update(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
        tree[id]=tree[id<<1]*tree[id<<1|1];
    }
    void query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            cur=cur*tree[id];
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        query(l,mid,id<<1,tl,tr);query(mid+1,r,id<<1|1,tl,tr);
    }
}

void solve(){
    int n,q;cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> c[i];
    Segtree::build(1,n,1);
    for(int i=1;i<=q;i++){
        int id,l,r;cin >> id >> l >> r;
        if(id==1) Segtree::update(1,n,1,l,r);
        else{
            int a,b;cin >> a >> b;
            cur.x[0][0]=a;cur.x[0][1]=b;
            Segtree::query(1,n,1,l,r);
            cout << cur.x[0][0] << ' ' << cur.x[0][1] << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
