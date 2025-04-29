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
#define se secon
const int mod=1e9;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,K;

struct poly{
    int a[405];
    poly(){memset(a,0,sizeof(a));}
    void operator+=(const poly &x){
        for(int i=0;i<=K;i++){
            a[i]+=x.a[i];
            a[i]%=mod;
        }
    }
    poly operator*(const poly&x){
        poly res;
        for(int i=0;i<=K;i++){
            if(a[i]){
                for(int j=0;i+j<=K;j++) res.a[i+j]=(res.a[i+j]+(1ll*a[i]*x.a[j]))%mod;
            }
        }
        return res;
    }
};
struct matrix{
    poly p[15][15];
    int n=-1,m=-1;
    matrix(int n=-1,int m=-1):n(n),m(m){}
    matrix operator*(const matrix &x){
        matrix res(n,x.m);
        for(int i=0;i<n;i++) for(int j=0;j<x.m;j++) for(int k=0;k<m;k++) res.p[i][j]+=p[i][k]*x.p[k][j];
        return res;
    }
}res(1,10),mul(10,10);

void solve(){
    cin >> n >> m >> K;n--;
    for(int i=1;i<=m;i++){
        int d,p;cin >> d >> p;
        mul.p[10-d][9].a[p]++;
    }
    for(int i=9;i>=1;i--) mul.p[i][i-1].a[0]++;
    res.p[0][9].a[0]=1;
    while(n){
        if(n&1) res=res*mul;
        mul=mul*mul;n>>=1;
    }
    int ans=0;
    for(int i=0;i<=K;i++) ans=(ans+res.p[0][9].a[i])%mod;
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
