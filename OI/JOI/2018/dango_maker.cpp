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
const int inf=1e9;
const int mod=998244353;
const int maxn=3005;
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
char c[maxn][maxn];
short int x[maxn][maxn];
short int dp[maxn][maxn][3][3];
void solve(){
    int n,m;cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin >> c[i][j];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i<=n-2 && c[i][j]=='R' && c[i+1][j]=='G' && c[i+2][j]=='W') x[i][j]^=2;
            if(j<=m-2 && c[i][j]=='R' && c[i][j+1]=='G' && c[i][j+2]=='W') x[i][j]^=1;
        }
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            short int res=0;
            for(int a=0;a<=2;a++){
                for(int b=0;b<=2-(a==1);b++){
                    for(int c=0;c<=2-(b==1 || a==1);c++){
                        short int nxt=dp[i-1][j+1][b][c]+((x[i][j]&a)>=1);
                        dp[i][j][a][b]=max(dp[i][j][a][b],nxt);
                    }
                    res=max(res,dp[i][j][a][b]);
                }
            }
            if(i==n || j==1) sum+=res;
        }
    }
    cout << sum << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}