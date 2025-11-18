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

__int128 dp[30][30][2];

void solve(){
    int n;cin >> n;
    dp[1][1][0]=1;
    for(int i=1;i<n;i++) for(int j=1;j<=i;j++){
        for(int k=0;k<=1;k++) for(int x=1;x<=j;x++) dp[i+1][x][k]+=dp[i][j][k];
        for(int x=j+1;x<=i+1;x++) dp[i+1][x][1]+=dp[i][j][0];
    }
    int res=0;
    for(int i=1;i<=n;i++){
        __int128 val=0;
        for(int j=1;j<=i;j++) val+=dp[i][j][1];
        for(int j=1;j<=i;j++) val*=(26-j+1);
        for(int j=1;j<=i;j++) val/=j;
        cout << (int)val << '\n';
        res=max(res,(int)val);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
