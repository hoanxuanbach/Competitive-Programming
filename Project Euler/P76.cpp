#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;
    vector<vector<int>> dp(N+1,vector<int>(N+1,0));
    for(int i=0;i<=N;i++) dp[0][i]=1;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++) dp[i][j]=dp[i-j][j]+dp[i][j-1];
        for(int j=i+1;j<=N;j++) dp[i][j]=dp[i][j-1];
    }
    cout << dp[N][N]-1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
