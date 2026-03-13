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

int dp[16][16][16][16][16][5];

void solve(){
    int n;cin >> n;n/=5;
    dp[0][0][0][0][0][0]=1;
    for(int a=0;a<=n;a++) for(int b=0;b<=n;b++) for(int c=0;c<=n;c++) for(int d=0;d<=n;d++) for(int e=0;e<=n;e++){
        for(int x=0;x<=4;x++){
            int val=dp[a][b][c][d][e][x];
            if(!val) continue;
            //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << x << ' ' << val << '\n';
            vector<int> f={a,b,c,d,e};
            int y=(x+1)%5;f[y]++;
            dp[f[0]][f[1]][f[2]][f[3]][f[4]][y]+=val;
            f[y]--;
            y=(x+4)%5;f[y]++;
            dp[f[0]][f[1]][f[2]][f[3]][f[4]][y]+=val;
            f[y]--;
        }
    }
    cout << dp[n][n][n][n][n][0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
