#include<bits/stdc++.h>
using namespace std;
#define maxn 105
#define maxm 10
#define pii pair<int,int>
int dp[maxn][65][65],n,m,ans;
vector<pii> ms[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int x=0;
        for(int j=1;j<=m;j++){
            char c;cin >> c;x<<=1;
            if(c=='P') x|=1;
        }
        for(int j=x;j;j=(j-1)&x){
            int pre=-3,cnt=0;
            bool ok=true;
            for(int k=0;k<m;k++){
                if(j&(1<<k)){
                    cnt++;
                    if(k-pre<3){ok=false;break;}
                    else pre=k;
                }
            }
            if(ok) ms[i].push_back({j,cnt});
        }
        ms[i].push_back({0,0});
    }
    for(int i=0;i<(int)ms[2].size();i++){
        for(int j=0;j<(int)ms[1].size();j++){
            int mask1=ms[2][i].first,mask2=ms[1][j].first;
            if((mask1&mask2)==0) dp[2][i][j]=ms[2][i].second+ms[1][j].second;
            ans=max(ans,dp[2][i][j]);
        }
    }
    for(int i=3;i<=n;i++){
        for(int j=0;j<(int)ms[i].size();j++){
            int mask=ms[i][j].first,cnt=ms[i][j].second;
            for(int p=0;p<(int)ms[i-1].size();p++){
                int ms2=ms[i-1][p].first;
                if((mask&ms2)!=0) continue;
                for(int q=0;q<(int)ms[i-2].size();q++){
                    int ms3=ms[i-2][q].first;
                    if((mask&ms3)!=0 || (ms2&ms3)!=0) continue;
                    dp[i][j][p]=max(dp[i][j][p],dp[i-1][p][q]+cnt);
                }
                ans=max(ans,dp[i][j][p]);
            }
        }
    }
    cout << ans << '\n';
}