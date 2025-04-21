#include<bits/stdc++.h>
using namespace std;
#define maxn 50005
#define maxl 20
#define maxk 5
const int inf=1e9;
int dp[maxn][maxl][maxk],n,m,k,t,Min[maxk],nMin[maxk];
int query(int u,int v){
    for(int i=0;i<k;i++) Min[i]=nMin[i]=inf;
    Min[u%k]=0;
    int ub=u/k,vb=v/k;
    for(int i=15;i>=0;i--){
        if((vb-ub)&(1<<i)){
            for(int j=0;j<k;j++) nMin[j]=inf;
            for(int p=0;p<k;p++){
                for(int j=0;j<k;j++){
                    int cur=ub*k+p;
                    nMin[j]=min(nMin[j],Min[p]+dp[cur][i][j]);
                }
            }
            ub+=(1<<i);
            for(int j=0;j<k;j++) Min[j]=nMin[j];
        }
    }
    return Min[v%k];
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> k >> n >> m >> t;
    for(int u=0;u<n;u++){
        for(int i=0;i<=15;i++){
            for(int j=0;j<k;j++) dp[u][i][j]=inf;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        dp[u][0][v%k]=w;
    }
    for(int i=1;i<=15;i++){
        for(int u=0;u<n;u++){
            for(int j=0;j<k;j++){
                dp[u][i][j]=inf;
                for(int p=0;p<k;p++){
                    int nxt=((u/k)+(1<<(i-1)))*k+p;
                    if(nxt>=n) continue;
                    dp[u][i][j]=min(dp[u][i][j],dp[u][i-1][p]+dp[nxt][i-1][j]);
                }
            }
        }
    }
    for(int i=1;i<=t;i++){
        int u,v;cin >> u >> v;
        int x=query(u,v);
        if(x==inf) cout << -1 << '\n';
        else cout << x << '\n';
    }
}
