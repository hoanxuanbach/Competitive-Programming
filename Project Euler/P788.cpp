#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    int res=0;
    for(int k=0;k<=1;k++){
        vector<vector<int>> dp(N+1,vector<int>(N+1,0));
        
        int val=0;
        if(k==0) dp[1][0]=9;
        else dp[1][0]=8,dp[1][1]=1,val++;
        for(int i=2;i<=N;i++){
            for(int j=0;j<=i;j++) for(int t=0;t<=9;t++) if(j>=(t==k)) dp[i][j]=(dp[i][j]+dp[i-1][j-(t==k)])%mod;
            for(int j=i/2+1;j<=i;j++) val=(val+dp[i][j])%mod;
        }
        //cout << k << ' ' << val << '\n';
        res=(res+val*(k?9:1))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
