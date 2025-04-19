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
const int maxn=1205;
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

int n,dp[maxn][maxn];
bool c[maxn];

void solve(){
    cin >> n;
    combi(2*n);
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        c[x]=1;
    }
    int a=0,b=0;
    dp[2*n+1][0]=1;
    for(int i=2*n;i>=1;i--){
        for(int j=b;j<=a+1;j++){
            if(!c[i]){
                dp[i][j]=(dp[i][j]+dp[i+1][j]*(j-b))%mod;
            }
            else{
                for(int k=1;k<=j;k++){
                    dp[i][j]=(dp[i][j]+dp[i+1][j-k]*C(a-j+k,k-1)%mod*C(2*k,k)%mod*fac[k-1]%mod)%mod;
                }
                dp[i][j]=(dp[i][j]+dp[i+1][j])%mod;
            }
            //cout << dp[i][j] << ' ';
        }
        //cout << '\n';
        if(c[i]) a++;
        else b++;
    }
    cout << dp[1][n]*power((mod+1)/2,n)%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
