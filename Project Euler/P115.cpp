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

int cal(int n,int m){
    vector<int> dp(n+1);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        if(i>=m) dp[i]++;
        for(int j=m;j<i;j++) dp[i]+=dp[i-j-1];
    }
    return dp[n];
}

void solve(){
    int m;cin >> m;

    int n=m;
    while(cal(n,m)<1000000){
        cout << n << ' ' << cal(n,m) << endl;
        n++;
    }
    cout << n << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
