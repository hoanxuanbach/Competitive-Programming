#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=605;
int n,pre[maxn][maxn][2],suf[maxn][maxn][2];
int nxt[maxn][2],sz[maxn],sum[maxn],dp[maxn][maxn];
string s[maxn];
int add(int a,int b){
    return (a+b>=mod?a+b-mod:a+b);
}
void build(int x){
    //cout << s[x] << '\n';
    memset(dp,0,sizeof(dp));
    nxt[sz[x]+1][0]=nxt[sz[x]+1][1]=0;
    for(int i=sz[x];i>=0;i--){
        nxt[i][0]=nxt[i+1][0];
        nxt[i][1]=nxt[i+1][1];
        if(i+1<=sz[x]) nxt[i][s[x][i+1]=='(']=i+1;
    }
    dp[0][0]=1;
    for(int i=0;i<=sz[x];i++){
        if(i) sum[x]=add(sum[x],dp[i][0]);
        for(int j=0;j<=i;j++){
            //cout << dp[i][j] << ' ';
            if(j>=1){
                if(nxt[i][0]) dp[nxt[i][0]][j-1]=add(dp[i][j],dp[nxt[i][0]][j-1]);
                else pre[x][j][0]=add(pre[x][j][0],dp[i][j]);
            }
            if(nxt[i][1]) dp[nxt[i][1]][j+1]=add(dp[i][j],dp[nxt[i][1]][j+1]);
            else pre[x][j][1]=add(pre[x][j][1],dp[i][j]);
        }
        //cout << '\n';
    }
    memset(dp,0,sizeof(dp));
    nxt[0][0]=nxt[0][1]=0;
    for(int i=1;i<=sz[x]+1;i++){
        nxt[i][0]=nxt[i-1][0];
        nxt[i][1]=nxt[i-1][1];
        if(i>1) nxt[i][s[x][i-1]==')']=i-1;
    }
    dp[sz[x]+1][0]=1;
    for(int i=sz[x]+1;i>=1;i--){
        for(int j=0;j<=sz[x]-i+1;j++){
            //cout << dp[i][j] << ' ';
            if(i<=sz[x]) suf[x][j][s[x][i]=='(']=add(suf[x][j][s[x][i]=='('],dp[i][j]);
            if(j>=1 && nxt[i][0]) dp[nxt[i][0]][j-1]=add(dp[i][j],dp[nxt[i][0]][j-1]);
            if(nxt[i][1]) dp[nxt[i][1]][j+1]=add(dp[i][j],dp[nxt[i][1]][j+1]);
        }
        //cout << '\n';
    }
    /*
    for(int i=0;i<=sz[x];i++) cout << pre[x][i][0] << ' ' << pre[x][i][1] << ' ';
    cout << '\n';
    for(int i=0;i<=sz[x];i++) cout << suf[x][i][0] << ' ' << suf[x][i][1] << ' ';
    cout << '\n';
    */
}
int merge(int x,int y){
    int ans=sum[x];
    for(int i=0;i<=min(sz[x],sz[y]);i++){
        for(int j=0;j<=1;j++) ans=add(ans,1LL*pre[x][i][j]*suf[y][i][j]%mod);
    }
    return ans;
}
signed main(){
    //freopen("BAJ.INP","r",stdin);
    //freopen("BAJ.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> s[i];sz[i]=(int)s[i].length();
        for(char &c:s[i]) c=(c=='L'?'(':')');
        s[i]="#"+s[i];
        build(i);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout << merge(i,j) << ' ';
        cout << '\n';
    }
}
