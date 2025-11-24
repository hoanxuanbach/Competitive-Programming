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
    int n;cin >> n;
    vector<vector<bool>> g(n,vector<bool>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g[i][j]=(__gcd(i,j)==1);
        }
    }

    int S=n*n;
    vector<vector<int>> dp(1<<S,vector<int>(S,0));
    dp[1<<0][0]=4;
    dp[1<<1][1]=8;
    dp[1<<(n+1)][n+1]=4;

    int res=0;
    for(int mask=0;mask<(1<<S);mask++) for(int i=0;i<S;i++) if(mask>>i&1){
        if(!dp[mask][i]) continue;
        if(__builtin_popcount(mask)>1) res+=dp[mask][i];

        int x=i/n,y=i%n;
        for(int dx=-x;dx<n-x;dx++) for(int dy=-y;dy<n-y;dy++){
            if(!g[abs(dx)][abs(dy)]) continue;
            int xt=x,yt=y;
            while(xt>=0 && yt>=0 && xt<n && yt<n && (mask>>(xt*n+yt)&1)) xt+=dx,yt+=dy;
            if(xt>=0 && yt>=0 && xt<n && yt<n){
                int ni=xt*n+yt;
                dp[mask|(1<<ni)][ni]+=dp[mask][i];
            }
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
