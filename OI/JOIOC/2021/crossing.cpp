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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
int c[]={1,3,9,8,20,24,22,14,16};
int n,s[3][maxn],f[3][maxn],cr[maxn];
namespace Segtree{
    int tree[4*maxn],lazy[4*maxn],num[3][4*maxn];
    void getnew(int id,int val){
        lazy[id]=val;
        tree[id]=num[val][id];
    }
    void pushdown(int id){
        if(lazy[id]==-1) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=-1;
    }
    void build(int l,int r,int id){
        lazy[id]=-1;
        if(l==r){
            for(int i=0;i<3;i++) num[i][id]=f[i][l];
            tree[id]=f[cr[l]][l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]&tree[id<<1|1];
        for(int i=0;i<3;i++) num[i][id]=num[i][id<<1]&num[i][id<<1|1];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]&tree[id<<1|1];
    }

}
void solve(){
    cin >> n;
    for(int i=0;i<3;i++){
        for(int j=1;j<=n;j++){
            char ch;cin >> ch;
            s[i][j]=(ch=='J'?0:(ch=='O'?1:2));
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<9;j++){
            int p=(s[0][i]*c[j]+s[1][i]*(c[j]/3)+s[2][i]*(c[j]/9))%3;
            f[p][i]+=(1<<j);
        }
    }
    int q;cin >> q;
    for(int i=1;i<=n;i++){
        char ch;cin >> ch;
        cr[i]=(ch=='J'?0:(ch=='O'?1:2));
    }
    Segtree::build(1,n,1);
    cout << (Segtree::tree[1]?"Yes":"No") << '\n';
    for(int i=1;i<=q;i++){
        int l,r;char ch;cin >> l >> r >> ch;
        int cc=(ch=='J'?0:(ch=='O'?1:2));
        Segtree::update(1,n,1,l,r,cc);
        cout << (Segtree::tree[1]?"Yes":"No") << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

