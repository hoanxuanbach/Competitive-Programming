#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
int n,m,a[maxn][maxn],dp[maxn][maxn][2];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){int u,v;cin >> u >> v;a[u][v]=a[v][u]=1;}
    for(int i=1;i<=n;i++) dp[i][(i+n-2)%n+1][0]=dp[i][(i+n-2)%n+1][1]=1;
    for(int i=n-2;i>=0;i--){
        for(int l=1;l<=n;l++){
            int r=(l+i-1)%n+1,nr=r%n+1,nl=(l+n-2)%n+1;
            dp[l][r][0]=(a[nl][l] && dp[nl][r][0]) || (a[nr][l] && dp[l][nr][1]);
            dp[l][r][1]=(a[nl][r] && dp[nl][r][0]) || (a[nr][r] && dp[l][nr][1]);
        }
    }
    int x=1;
    while(x<=n && !dp[x][x][0] && !dp[x][x][1]) x++;
    if(x>n){
        cout << -1 << '\n';
        return 0;
    }
    int y=x,t=(dp[x][y][0]?0:1);

    cout << x << '\n';
    for(int i=1;i<n;i++){
        int ny=y%n+1,nx=(x+n-2)%n+1;;
        if(t==0){
            if(a[nx][x] && dp[nx][y][0]){
                cout << nx << '\n';
                x=nx;t=0;
            }
            else if(a[ny][x] && dp[x][ny][1]){
                cout << ny << '\n';
                y=ny;t=1;
            }
        }
        else{
            if(a[nx][y] && dp[nx][y][0]){
                cout << nx << '\n';
                x=nx;t=0;
            }
            else if(a[ny][y] && dp[x][ny][1]){
                cout << ny << '\n';
                y=ny;t=1;
            }
        }
    }

}
