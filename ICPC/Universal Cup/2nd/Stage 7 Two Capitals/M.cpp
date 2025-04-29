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
int mod;
const int maxn=405;
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
const int base=131;

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int catalan(int n){
    return (C(2*n,n)-C(2*n,n+1)+mod)%mod;
}

int n,f[maxn],g[maxn],res[maxn];
int dp[maxn][maxn],d[maxn][maxn];

void solve(){
    cin >> n >> mod;
    combi(2*n);
    g[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++) g[i]=(g[i]+C(2*i,2*j)*catalan(j)%mod*catalan(i-j)%mod)%mod;
    }
    dp[0][0]=1;
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=i;k+=2) dp[i][j]=(dp[i][j]+dp[i-k][j-1]*g[k/2]%mod)%mod;
        }
    }
    f[0]=1;
    for(int i=1;i<=n;i++){
        f[i]=g[i]*power(2,mod-2)%mod;
        for(int j=1;j<i;j++) f[i]=(f[i]-dp[2*i][2*j]*f[j]%mod+mod)%mod;
    }
    d[0][0]=res[0]=1;
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=i;k+=2) d[i][j]=(d[i][j]+d[i-k][j-1]*res[k/2]%mod)%mod;
        }
        if(i%2==0){
            for(int j=1;j<=i/2;j++) res[i/2]=(res[i/2]+d[i][2*j]*f[j])%mod;
            cout << res[i/2] << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
