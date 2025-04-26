#include <bits/stdc++.h>
using namespace std;
int dx[]={0,-1,0,1},
    dy[]={-1,0,1,0};

int N,M,cnt;
vector<string> C;
vector<vector<int>> id[2];


bool cc(int x,int y){
    return (x<0 || y<0 || x>=N || y>=M || C[x][y]=='#');
}

int yellowblue(int _N, int _M, vector<string> _C)
{
    N=_N;M=_M;C=_C;
    for(int k=0;k<=1;k++){
        id[k].assign(N,vector<int>(M,-1));
        for(int i=0;i<N;i++) for(int j=0;j<M;j++) if(C[i][j]=='.'){
            if(cc(i+dx[k],j+dy[k])) id[k][i][j]=cnt++;
            else id[k][i][j]=id[k][i+dx[k]][j+dy[k]];
        }
    }
    vector<vector<int>> edge(cnt);
    for(int i=0;i<N;i++) for(int j=0;j<M;j++) if(C[i][j]=='.'){
        for(int k=0;k<=1;k++){
            if(cc(i+dx[k],j+dy[k]) || cc(i+dx[k+2],j+dy[k+2])){
                edge[id[k][i][j]].push_back(id[k^1][i][j]);
            }
        }
    }
    vector<bool> vis(cnt,false);
    vector<int> order;
    function<void(int)> dfs = [&](int u){
        vis[u]=true;
        for(int v:edge[u]) if(!vis[v]) dfs(v);
        order.push_back(u);
    };
    for(int i=0;i<cnt;i++) if(!vis[i]) dfs(i);

    int num=0;
    vector<int> scc(cnt,-1);
    vector<vector<int>> rev_edge(cnt);
    for(int i=0;i<cnt;i++) for(int v:edge[i]) rev_edge[v].push_back(i);

    function<void(int)> dfs2 = [&](int u){
        scc[u]=num;
        for(int v:rev_edge[u]) if(scc[v]==-1) dfs2(v);
    };
    for(int i=0;i<cnt;i++){
        int u=order[cnt-i-1];
        if(scc[u]==-1){
            dfs2(u);
            num++;
        }
    }

    vector<vector<int>> scc_edge(num);
    for(int i=0;i<cnt;i++) for(int v:edge[i]) if(scc[i]!=scc[v]) scc_edge[scc[i]].push_back(scc[v]);
    vis.assign(num,false);
    order.clear();

    function<void(int)> dfs3 = [&](int u){
        vis[u]=true;
        for(int v:scc_edge[u]) if(!vis[v]) dfs3(v);
        order.push_back(u);
    };

    for(int i=0;i<num;i++) if(!vis[i]) dfs3(i);
    reverse(order.begin(),order.end());
    for(int i=0;i<(int)order.size()-1;i++){
        bool check=false;
        for(int v:scc_edge[order[i]]) if(order[i+1]==v) check=true;
        if(!check) return 0;
    }
    return 1;
}
