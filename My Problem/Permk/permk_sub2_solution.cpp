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
int fac[maxn];

void solve(){
    int n,k;cin >> n >> k;
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;

    vector<vector<int>> dp(k,vector<int>(k,0));
    dp[k-1][0]=fac[k];

    for(int i=k+1;i<=n;i++){
        vector<vector<int>> ndp(k,vector<int>(k,0));
        for(int i=1;i<k;i++) for(int j=0;j+1<k;j++) (ndp[i][j+1]+=dp[i][j])%=mod;
        for(int i=k-2;i>=1;i--) for(int j=0;j<k;j++) (ndp[i][j]+=ndp[i+1][j])%=mod;
        for(int i=1;i<k;i++) for(int j=0;j<k;j++){
            int ni=i+1,nj=j+1;
            if(ni==k) ni--,nj=0;
            if(nj<k) (ndp[ni][nj]+=dp[i][j]*(k-i))%=mod;
        }
        swap(dp,ndp);
    }
    cout << dp[k-1][0] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}