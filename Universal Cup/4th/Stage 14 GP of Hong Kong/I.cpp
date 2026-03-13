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

void solve(){
    int n,m;cin >> n >> m;
    vector<vector<int>> p(m,vector<int>(n)),f(m,vector<int>(n+1));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++) cin >> p[i][j],f[i][p[i][j]]=j;
    }

    vector<vector<bool>> T(n,vector<bool>(n,0));
    for(int x=1;x<=n;x++){
        int l=f[0][x],s=n;
        vector<int> pos(m),cnt(n+1);
        for(int i=0;i<m;i++) pos[i]=f[i][x],s=min(s,n-pos[i]);
        T[l][l]=1;

        int num=0;
        for(int k=1;k<s;k++){
            for(int i=0;i<m;i++) if((++cnt[p[i][pos[i]+k]])==m) num++;
            if(num==k) T[l][l+k]=1;
        }
    }
    vector<vector<int>> dp(n+1,vector<int>(n,0));
    dp[n][n-1]=1;
    for(int l=n-1;l>=1;l--){
        dp[l][l-1]=1;
        for(int r=l;r<n;r++) for(int k=l;k<=r;k++) if(T[l][k]) dp[l][r]=(dp[l][r]+dp[l+1][k]*dp[k+1][r])%mod;
    }
    cout << dp[1][n-1] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}