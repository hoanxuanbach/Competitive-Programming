#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
const int inf=1e9;
int n,dp[maxn][2][2],a[maxn];
signed main(){
    //freopen("ORN.INP","r",stdin);
    //freopen("ORN.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++) dp[1][i][j]=i;
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<=1;j++){
            for(int k=0;k<=1;k++){
                dp[i][j][k]=n+1;
                int cur=(j?(k?-inf:inf):a[i]);
                for(int p=0;p<=1;p++){
                    int pre=(p?(k?inf:-inf):a[i-1]);
                    if((k&&pre>cur) || (!k && pre<cur)) dp[i][j][k]=min(dp[i][j][k],dp[i-1][p][k^1]+j);
                }
            }
        }
    }
    int ans=inf;
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++) ans=min(ans,dp[n][i][j]);
    }
    cout << ans << '\n';
}
