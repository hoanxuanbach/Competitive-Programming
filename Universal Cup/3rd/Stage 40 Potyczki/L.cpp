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

const int N = 505;

void solve(){
    int n,m;cin >> n >> m;
    vector<bitset<N>> e(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        e[u][v]=1;
    }
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    for(int x=n;x>=1;x--){
        for(int y=x;y<=n;y++){
            if(e[x][y]){
                e[x]|=e[y];
                dp[x][y]=1;
                for(int i=x+1;i<y;i++) dp[x][y]+=min(dp[x][i],dp[i][y]);
            }
        }
    }
    cout << dp[1][n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
