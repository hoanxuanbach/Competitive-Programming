#include<bits/stdc++.h>
using namespace std;
#define maxa 1000005
#define pii pair<int,int>
const int inf=1e9;
int dist[maxa][6],p10[6],a,b;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> a >> b;
    p10[0]=1;
    for(int i=1;i<=5;i++) p10[i]=p10[i-1]*10;
    for(int i=0;i<1000000;i++){
        for(int j=0;j<6;j++) dist[i][j]=-1;
    }
    dist[a][5]=0;
    queue<pii> q;q.push({a,5});
    while(!q.empty()){
        int u=q.front().first,p=q.front().second;q.pop();
        if(u==b){
            cout << dist[u][p] << '\n';
            return 0;
        }
        int d=(u/p10[p])%10,d1=u%10,d2=(u/p10[5])%10;
        int nxt0=u+(d2-d)*(p10[p]-p10[5]),nxt1=u+(d1-d)*(p10[p]-1);
        if(dist[nxt0][p]==-1){
            dist[nxt0][p]=dist[u][p]+1;
            q.push({nxt0,p});
        }
        if(dist[nxt1][p]==-1){
            dist[nxt1][p]=dist[u][p]+1;
            q.push({nxt1,p});
        }
        if(d<9 && dist[u+p10[p]][p]==-1){
            dist[u+p10[p]][p]=dist[u][p]+1;
            q.push({u+p10[p],p});
        }
        if(d>0 && dist[u-p10[p]][p]==-1){
            dist[u-p10[p]][p]=dist[u][p]+1;
            q.push({u-p10[p],p});
        }
        if(p>0 && dist[u][p-1]==-1){
            dist[u][p-1]=dist[u][p]+1;
            q.push({u,p-1});
        }
        if(p<5 && dist[u][p+1]==-1){
            dist[u][p+1]=dist[u][p]+1;
            q.push({u,p+1});
        }
    }
}