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

const int N = 25;
int dp[N][N][N],C[N][N];

void solve(){
    int n,k;cin >> n >> k;
    vector<int> d(n+1);
    for(int i=1;i<=n;i++) cin >> d[i];
    for(int i=n;i>=1;i--) d[i]=d[i]-d[i-1]-1;

    for(int i=0;i<=k;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int x=0;x<=k;x++) for(int y=0;y<=x;y++){
            if(!dp[i-1][x][y]) continue;
            for(int a=max(0LL,-d[i]);a<=k-x;a++) for(int b=0;b<=min(d[i]+a,x-y);b++){
                dp[i][x+a][y+b]=(dp[i][x+a][y+b]+dp[i-1][x][y]*C[k-x][a]%mod*C[x-y][b])%mod;
            }
        }
    }

    int total=0;
    for(int i=0;i<=k;i++) total=(total+dp[n][k][i])%mod;
    cout << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
