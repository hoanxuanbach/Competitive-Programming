#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e5;

int dp[105][15][15],cnt[105][15][15],pw[105];

void solve(){
    int n;cin >> n;pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*10%mod;

    int res=0;
    for(int d=1;d<=10;d++) for(int k=0;k<=9;k++){
        memset(dp,0,sizeof(dp));
        memset(cnt,0,sizeof(cnt));

        cnt[1][0][k]=1;dp[1][0][k]=k;
        for(int i=1;i<n;i++) for(int j=0;j<=9;j++) for(int x=0;x<=9;x++){
            int nj=(x*d+j)/10,y=(x*d+j)%10;
            (dp[i+1][nj][y]+=dp[i][j][x]+cnt[i][j][x]*pw[i]*y)%=mod;
            (cnt[i+1][nj][y]+=cnt[i][j][x])%=mod;
        }
        for(int i=2;i<=n;i++) for(int j=0;j<=9;j++){
            if(k<j) continue;
            if((k-j)%d!=0) continue;
            int x=(k-j)/d;
            if(!x) continue;
            (res+=dp[i][j][x])%=mod;
            //if(cnt[i][j][x]) cout << i << ' ' << j << ' ' << x << ' ' << dp[i][j][x] << ' ' << cnt[i][j][x] << '\n';
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
