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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

struct matrix{
    int n,m;
    vector<vector<int>> x;
    matrix(int n=0,int m=0):n(n),m(m){
        x.assign(n,vector<int>(m,0));
    }
    friend matrix operator*(matrix a,matrix b){
        matrix c(a.n,b.m);
        for(int i=0;i<a.n;i++) for(int j=0;j<b.m;j++){
            c.x[i][j]=0;
            for(int k=0;k<a.m;k++) c.x[i][j]=(c.x[i][j]+a.x[i][k]*b.x[k][j])%mod;
        }
        return c;
    }
};

matrix s0(3,3),s1(3,3);

matrix power(matrix a,int n){
    matrix res(3,3);
    for(int i=0;i<3;i++) res.x[i][i]=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
    }
    return res;
}

matrix cal(int a,int b,matrix m0,matrix m1){
    if(a==0) return power(m1,b);
    if(b==0) return power(m0,a);
    if(b>=a) return cal(a,b%a,m0*power(m1,b/a),m1);
    else return cal(a-(a-1)/b*b,b,m0,m1*power(m0,(a-1)/b));
}
void solve(){
    int a,b;cin >> a >> b;
    cout << cal(a,b,s0,s1).x[0][0] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    s0.x = {{2, 0, 1},{0, 1, 0},{mod-1, 0, 0}};
    s1.x = {{2, 1, 0},{mod-1, 0, 0},{0, 0, 1}};
    int test=1;cin >> test;
    while(test--) solve();
}