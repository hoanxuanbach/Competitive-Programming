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

int dp[20][20][20][20];

void solve(){
    int n;cin >> n;
    dp[1][9][1][0]=9;
    for(int i=1;i<n;i++) for(int a=0;a<=10;a++) for(int b=0;b<=10-a;b++) for(int c=0;c<=10-a-b;c++){
        int d=10-a-b-c;
        if(a) dp[i+1][a-1][b+1][c]+=dp[i][a][b][c]*a;
        if(b) dp[i+1][a][b-1][c+1]+=dp[i][a][b][c]*b;
        if(c) dp[i+1][a][b][c-1]+=dp[i][a][b][c]*c;
    }
    int res=0;
    for(int a=0;a<=10;a++) for(int b=0;b<=10-a;b++) for(int c=0;c<=10-a-b;c++) res+=dp[n][a][b][c];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
