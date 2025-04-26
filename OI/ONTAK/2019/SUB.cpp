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
const int maxn=500005;
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
const int base=101;

struct matrix{
    int n,m;
    int x[5][5];
    matrix(int n=5,int m=5):n(n),m(m){
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
int num[305],n,q,c[maxn];
matrix mt[10];

matrix tree[4*maxn];
void build(int l,int r,int id){
    if(l==r){
        tree[id]=mt[c[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]*tree[id<<1|1];
}
matrix cur(1,5);
void query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        cur=cur*tree[id];
        return;
    }
    int mid=(l+r)>>1;
    query(l,mid,id<<1,tl,tr);query(mid+1,r,id<<1|1,tl,tr);
}

void solve(){
    num['A']=1;
    num['C']=2;
    num['G']=3;
    num['T']=4;
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        char ch;cin >> ch;
        c[i]=num[ch];
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++) mt[i].x[j][j]=1;
        mt[i].x[0][i]=1;
        mt[i].x[0][0]=2;
        mt[i].x[i][i]=0;
        mt[i].x[i][0]=mod-1;
    }
    build(1,n,1);
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        cur.x[0][0]=1;
        for(int j=1;j<=4;j++) cur.x[0][j]=0;
        query(1,n,1,l,r);
        cout << (cur.x[0][0]+mod-1)%mod << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
