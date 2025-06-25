#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1e9+7;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;

    {//first problem
        vector<int> dp(n+5);
        dp[0]=dp[1]=1;
        for(int i=2;i<=n;i++) dp[i]=(dp[i-1]+dp[i-2]*(i-1))%mod;
        cout << dp[n] << ' ';
    }

    {//second problem
        vector<int> dp(n+5);
        dp[0]=1;
        for(int i=3;i<=n;i++) dp[i]=((i-1)*dp[i-1]+(i-1)*(i-2)%mod*dp[i-3])%mod;
        cout << dp[n] << '\n';
    }

}