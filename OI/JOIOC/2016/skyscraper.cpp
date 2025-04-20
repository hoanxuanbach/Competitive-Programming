#include<bits/stdc++.h>
using namespace std;
#define maxn 105
#define maxl 1005
#define int long long
const int mod=1e9+7;
int dp[2][maxn][maxl][2][2],n,a[maxn],l,t;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> l;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    for(int p=0;p<=1;p++){
        for(int q=0;q<=1;q++) dp[1][1][0][p][q]=1;
    }
    for(int i=1;i<n;i++){
        t^=1;
        for(int j=1;j<=i;j++){
            for(int k=0;k<=l;k++){
                for(int p=0;p<=1;p++){
                    for(int q=0;q<=1;q++){
                        int nk=k+(2*j-p-q)*(a[i+1]-a[i]);
                        int v=dp[t][j][k][p][q];dp[t][j][k][p][q]=0;
                        if(nk>l) continue;
                        dp[t^1][j][nk][p][q]=(dp[t^1][j][nk][p][q]+(2*j-p-q)*v)%mod;
                        dp[t^1][j-1][nk][p][q]=(dp[t^1][j-1][nk][p][q]+(j-1)*v)%mod;
                        dp[t^1][j+1][nk][p][q]=(dp[t^1][j+1][nk][p][q]+(j+1-p-q)*v)%mod;
                        if(!p){
                            dp[t^1][j][nk][1][q]=(dp[t^1][j][nk][1][q]+v)%mod;
                            dp[t^1][j+1][nk][1][q]=(dp[t^1][j+1][nk][1][q]+v)%mod;
                        }
                        if(!q){
                            dp[t^1][j][nk][p][1]=(dp[t^1][j][nk][p][1]+v)%mod;
                            dp[t^1][j+1][nk][p][1]=(dp[t^1][j+1][nk][p][1]+v)%mod;
                        }
                    }
                }
            }
        }
    }
    int ans=0;t^=1;
    for(int i=0;i<=l;i++) ans=(ans+dp[t][1][i][1][1])%mod;
    cout << ans << '\n';
}