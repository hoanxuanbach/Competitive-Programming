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

int dp[105][2];

void solve(){
    int N;cin >> N;
    __int128 X=1;
    for(int i=0;i<N;i++) X*=10;

    dp[100][0]=1;
    for(int i=100;i>=1;i--) for(int j=0;j<=1;j++){
        int k=(X>>(i-1)&1);
        int nj=j*2+k;
        for(int d=0;d<=2;d++) if(nj>=d && nj-d<=1) dp[i-1][nj-d]+=dp[i][j];
    }
    cout << dp[0][0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
