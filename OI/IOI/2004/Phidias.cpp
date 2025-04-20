#include<bits/stdc++.h>
using namespace std;
const int maxn = 605;
int n,m,k,dp[maxn][maxn];
int a[maxn],b[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    for(int i=1;i<=k;i++) cin >> a[i] >> b[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int x=1;x<i;x++) dp[i][j]=max(dp[i][j],dp[x][j]+dp[i-x][j]);
            for(int x=1;x<j;x++) dp[i][j]=max(dp[i][j],dp[i][x]+dp[i][j-x]);
            for(int x=1;x<=k;x++) if(a[x]<=i && b[x]<=j) dp[i][j]=max(dp[i][j],a[x]*b[x]);
            //cout << dp[i][j] << ' ';
        }
        //cout << '\n';
    }
    cout << n*m-dp[n][m] << '\n';
}
