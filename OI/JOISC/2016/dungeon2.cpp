#include "dungeon2.h"
#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 205;
namespace dungeon2{

    int d[maxn][maxn],p[maxn][maxn],e[maxn][maxn],deg[maxn],res[maxn];
    int N,T=1;

    void pre_dfs(){
        int u=++N;
        deg[u]=NumberOfRoads();
        for(int i=1;i<=deg[u];i++){
            Move(i,2);
            int id=LastRoad();
            int col=Color();
            if(col==1){
                p[u][i]=N+1;
                e[u][i]=1;
                e[N+1][id]=-1;
                pre_dfs();
                Move(id,3);
            }
            else if(col==2) Move(id,2);
            else{
                e[u][i]=-1;
                Move(id,3);
            }
        }
    }

    void dfs(int u){
        int col=(u/T)%3+1;
        for(int i=1;i<=deg[u];i++){
            if(!e[u][i]){
                Move(i,col);
                int id=LastRoad();
                int ncol=Color();
                p[u][i]+=(ncol-1)*T;
                Move(id,ncol);
            }
        }
        for(int i=1;i<=deg[u];i++){
            if(e[u][i]==1){
                Move(i,col);
                int id=LastRoad();
                dfs(p[u][i]);
                Move(id,1);
            }
        }
    }
    void Inspect(int R)
    {
        pre_dfs();
        for(int i=0;i<5;i++) dfs(1),T*=3;
        for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) d[i][j]=inf;
        for(int i=1;i<=N;i++){
            for(int j=1;j<=deg[i];j++) if(p[i][j]>=1){
                d[i][p[i][j]]=d[p[i][j]][i]=1;
            }
        }
        for(int k=1;k<=N;k++){
            for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        }
        for(int i=1;i<=N;i++) for(int j=i+1;j<=N;j++) if(d[i][j]<=R) res[d[i][j]]++;
        for(int i=1;i<=R;i++) Answer(i,res[i]);
    }
}

void Inspect(int R)
{
    dungeon2::Inspect(R);
}
