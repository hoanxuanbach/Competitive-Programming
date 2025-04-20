#include "garden.h"
#include "gardenlib.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 150005;
int f[maxn],g[maxn][2],cnt;
int nxt[2*maxn],num[2*maxn],dist[2*maxn],total[2*maxn];
bool vis[2*maxn];
vector<int> edge[2*maxn];

void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
{
    for(int i=0;i<M;i++){
        int u=R[i][0],v=R[i][1];
        int a=(f[u]!=0),b=(f[v]!=0);
        if(!g[u][a]) g[u][a]=++cnt;
        if(!g[v][b]) g[v][b]=++cnt;
        if(!f[u]) f[u]=g[v][b];
        else if(f[u]!=-1){
            nxt[g[u][a]]=f[u];
            nxt[g[u][0]]=g[v][b];
            f[u]=-1;
        }
        if(!f[v]) f[v]=g[u][a];
        else if(f[v]!=-1){
            nxt[g[v][b]]=f[v];
            nxt[g[v][0]]=g[u][a];
            f[v]=-1;
        }
    }
    for(int v=0;v<N;v++){
        if(f[v]>0) nxt[g[v][0]]=f[v],num[g[v][0]]++;
        else if(f[v]==-1) num[g[v][1]]++;
        //for(int j=0;j<2;j++) if(g[v][j]) cout << v << ' ' << j << ' ' << g[v][j] << ' ' << nxt[g[v][j]] << '\n';
    }
    auto cal = [&](int x){
        if(!x) return vector<int>(Q,0);
        for(int i=0;i<=cnt;i++){
            vis[i]=false;
            edge[i].clear();
            total[i]=0;
        }
        int u=x;
        vector<int> cycle;
        while(!vis[u]){
            cycle.push_back(u);
            vis[u]=true,u=nxt[u];
        }
        for(int i=1;i<=cnt;i++) if(!vis[i]) edge[nxt[i]].push_back(i);
        int sz=(int)cycle.size();
        function<void(int)> dfs = [&](int v){
            total[dist[v]]+=num[v];
            for(int k:edge[v]){
                dist[k]=dist[v]+1;
                dfs(k);
            }
        };
        dist[x]=0;dfs(x);
        if(u==x){
            for(int i=1;i<(int)cycle.size();i++){
                dist[cycle[i]]=sz-i;
                dfs(cycle[i]);
            }
            for(int i=sz;i<=cnt;i++) total[i]+=total[i-sz];
        }
        vector<int> res(Q);
        for(int i=0;i<Q;i++){
            if(G[i]<=cnt) res[i]=total[G[i]];
            else if(u==x){
                int d=G[i]%sz;
                d=((cnt-d)/sz)*sz+d;
                res[i]=total[d];
            }
        }
        return res;
    };
    vector<int> a=cal(g[P][0]),b=cal(g[P][1]);
    for(int i=0;i<Q;i++) answer(a[i]+b[i]);
}


