#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 205
int dp[maxn][maxn],num[maxn][maxn],trace[maxn][maxn],n,ans[maxn];
int query(int x,int y){
    if(x>y) return 0;
    return (num[y][x-1]-num[x-1][x-1]+num[y][n]-num[x-1][n]-num[y][y]+num[x-1][y]);
}
int solve(int x,int y){
    if(x>y) return 0;
    if(dp[x][y]!=-1) return dp[x][y];
    int ans=LLONG_MAX,id;
    for(int i=x;i<=y;i++){
        int a=solve(x,i-1)+solve(i+1,y)+query(x,i-1)+query(i+1,y);
        if(a<ans){ans=a;id=i;}
    }
    trace[x][y]=id;
    return dp[x][y]=ans;
}
void tracing(int x,int y,int par){
    if(x>y) return;
    int a=trace[x][y];
    ans[a]=par;
    tracing(x,a-1,a);tracing(a+1,y,a);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> num[i][j];dp[i][j]=-1;
            num[i][j]+=(num[i][j-1]+num[i-1][j]-num[i-1][j-1]);
        }
    }
    solve(1,n);
    tracing(1,n,0);
    for(int i=1;i<=n;i++) cout << ans[i] << " ";
}
