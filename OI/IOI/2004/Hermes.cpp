#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 2005;
const int D = 1000;
int dp[2][2][maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    int t=0,px=0,py=0;
    for(int i=0;i<=2*D;i++) dp[t][0][i]=dp[t][1][i]=inf;
    dp[t][0][D]=dp[t][1][D]=0;
    for(int k=1;k<=n;k++){
        t^=1;
        for(int i=0;i<=2*D;i++) dp[t][0][i]=dp[t][1][i]=inf;
        int x,y;cin >> x >> y;
        for(int i=0;i<=2*D;i++){
            //if(dp[t^1][0][i]!=inf || dp[t^1][1][i]!=inf) cout << k << ' ' << 0 << ' ' << i-D << ' ' << dp[t^1][0][i] << ' ' << dp[t^1][1][i] << '\n';
            dp[t][0][i]=min(dp[t][0][i],dp[t^1][0][i]+abs(py-y));
            dp[t][1][py+D]=min(dp[t][1][py+D],dp[t^1][0][i]+abs(i-D-x));
            dp[t][1][i]=min(dp[t][1][i],dp[t^1][1][i]+abs(px-x));
            dp[t][0][px+D]=min(dp[t][0][px+D],dp[t^1][1][i]+abs(i-D-y));
        }
        px=x,py=y;
    }
    int res=inf;
    for(int i=0;i<=2*D;i++) res=min({res,dp[t][0][i],dp[t][1][i]});
    cout << res << '\n';
}
