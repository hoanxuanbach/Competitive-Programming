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

int dp[35][2][3];

void solve(){
    int n;cin >> n;
    dp[0][0][0]=1;
    for(int i=0;i<n;i++) for(int j=0;j<=1;j++) for(int k=0;k<=2;k++){
        if(k<2) dp[i+1][j][k+1]+=dp[i][j][k];
        if(!j) dp[i+1][1][0]+=dp[i][j][k];
        dp[i+1][j][0]+=dp[i][j][k];
    }
    int res=0;
    for(int i=0;i<=1;i++) for(int j=0;j<=2;j++) res+=dp[n][i][j];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
