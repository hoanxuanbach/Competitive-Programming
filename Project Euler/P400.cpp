#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e18;
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
    int n;cin >> n;
    
    vector<int> f(n+1);f[2]=1;
    for(int i=3;i<=n;i++) f[i]=(f[i-1]+1)^(f[i-2]+1);
    
    int S=*max_element(f.begin(),f.end()),T=1;
    while(T<=S) T<<=1;
    vector<vector<int>> dp(n+1,vector<int>(T));
    dp[1][0]=1;
    dp[2][0]=dp[2][1]=1;
    for(int i=3;i<=n;i++){
        dp[i][0]=1;
        for(int j=1;j<T;j++) dp[i][j]=(dp[i-1][(j-1)^(f[i-2]+1)]+dp[i-2][(j-1)^(f[i-1]+1)])%mod;
    }
    cout << dp[n][1] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
