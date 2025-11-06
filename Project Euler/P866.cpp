#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 987654319;
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
    vector<vector<int>> C(N+1,vector<int>(N+1,0));
    for(int i=0;i<=N;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
    vector<int> dp(N+1);
    dp[0]=1;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++){
            dp[i]=(dp[i]+dp[j-1]*dp[i-j]%mod*C[i-1][j-1])%mod;
        }
        dp[i]=dp[i]*i*(2*i-1)%mod;
    }
    int val=1;
    for(int i=1;i<=N;i++) val=val*i%mod;
    cout << dp[N]*power(val,mod-2)%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
