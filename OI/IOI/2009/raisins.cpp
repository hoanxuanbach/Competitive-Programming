#include<bits/stdc++.h>
using namespace std;
const int maxn = 55;
const int inf = 1e9;
int n,m,p[maxn][maxn];
int f(int x,int y,int u,int v){
    return p[u][v]-p[x-1][v]-p[u][y-1]+p[x-1][y-1];
}
int dp[maxn][maxn][maxn][maxn];
int g(int x,int y,int u,int v){
    if(x==u && y==v) return 0;
    if(dp[x][y][u][v]) return dp[x][y][u][v];
    int res=inf,val=f(x,y,u,v);
    for(int i=x;i<u;i++) res=min(res,val+g(x,y,i,v)+g(i+1,y,u,v));
    for(int i=y;i<v;i++) res=min(res,val+g(x,y,u,i)+g(x,i+1,u,v));
    return dp[x][y][u][v]=res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin >> p[i][j],p[i][j]+=p[i-1][j]+p[i][j-1]-p[i-1][j-1];
    cout << g(1,1,n,m) << '\n';
}
