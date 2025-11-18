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

int dp[45][1030][15];

void solve(){
    int N=40;
    for(int i=1;i<=N;i++){
        for(int x=1;x<=9;x++) dp[i][1<<x][x]++;
        for(int mask=0;mask<(1<<10);mask++) for(int x=0;x<=9;x++){
            if(x>0){
                int y=x-1;
                dp[i][mask|(1<<y)][y]+=dp[i-1][mask][x];
            }
            if(x<9){
                int y=x+1;
                dp[i][mask|(1<<y)][y]+=dp[i-1][mask][x];
            }
        }
    }
    int res=0;
    for(int x=0;x<=9;x++) res+=dp[N][1023][x];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
