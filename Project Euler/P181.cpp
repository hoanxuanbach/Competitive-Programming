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
    int N,M;cin >> N >> M;
    vector<vector<int>> dp(N+1,vector<int>(M+1,0));
    dp[0][0]=1;
    for(int x=0;x<=N;x++) for(int y=0;y<=M;y++){
        if(!(x+y)) continue;
        for(int i=x;i<=N;i++) for(int j=y;j<=M;j++) dp[i][j]+=dp[i-x][j-y];
    }
    cout << dp[N][M] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
