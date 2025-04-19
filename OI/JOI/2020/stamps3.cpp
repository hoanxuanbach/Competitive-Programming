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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define pii pair<int,int>
const int inf=1000000005;
const int mod=998244353;
const int maxn=205;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int dp[maxn][maxn][maxn][2],n,L,x[maxn],t[maxn];
void solve(){
    cin >> n >> L;x[n+1]=L;
    for(int i=1;i<=n;i++) cin >> x[i];
    for(int i=1;i<=n;i++) cin >> t[i];
    for(int i=0;i<=n+1;i++){
        for(int l=0;l<=n+1-i;l++){
            int r=l+i;
            for(int k=0;k<=n+1-i;k++){
                for(int j=0;j<=1;j++) dp[l][r][k][j]=inf;
            }
        }
    }
    dp[0][n+1][0][0]=dp[0][n+1][0][1]=0;
    int res=0;
    for(int i=n+1;i>=1;i--){
        for(int l=0;l<=n+1-i;l++){
            int r=l+i;
            for(int k=0;k<=n+1-i;k++){
                int nxt0=dp[l][r][k][0],nxt1=dp[l][r][k][1];
                if(nxt0!=inf){
                    res=max(res,k);
                    int ok0=x[l+1]-x[l]+nxt0,ok1=x[l]+x[n+1]-x[r-1]+nxt0;
                    dp[l+1][r][k+(ok0<=t[l+1])][0]=min(dp[l+1][r][k+(ok0<=t[l+1])][0],ok0);
                    dp[l][r-1][k+(ok1<=t[r-1])][1]=min(dp[l][r-1][k+(ok1<=t[r-1])][1],ok1);
                }
                if(nxt1!=inf){
                    res=max(res,k);
                    int ok0=x[l+1]+x[n+1]-x[r]+nxt1,ok1=x[r]-x[r-1]+nxt1;
                    dp[l+1][r][k+(ok0<=t[l+1])][0]=min(dp[l+1][r][k+(ok0<=t[l+1])][0],ok0);
                    dp[l][r-1][k+(ok1<=t[r-1])][1]=min(dp[l][r-1][k+(ok1<=t[r-1])][1],ok1);
                }
            }
        }
    }
    cout << res << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}