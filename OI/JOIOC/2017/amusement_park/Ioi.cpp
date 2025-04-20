#include "Ioi.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

long long Ioi(int N, int M, int A[], int B[], int P, int V, int T) {
    vector<vector<int>> adj(N),edge(N);
    for(int i=0;i<M;i++) edge[A[i]].push_back(B[i]),edge[B[i]].push_back(A[i]);
    vector<bool> vis(N,false);
    int cur=0;
    vector<int> deg(N,0),num(N,-1);
    vector<pii> pp;
    function<void(int)> dfs = [&](int u){
        vis[u]=true;
        if(cur<60) num[u]=cur++;
        for(int v:edge[u]){
            if(vis[v]) continue;
            adj[u].push_back(v);
            if(cur<60){
                pp.push_back({u,v});
                deg[u]++;deg[v]++;
            }
            dfs(v);
        }
    };
    dfs(0);
    long long res=0;
    function<void(int,int)> cal = [&](int u,int p){
        for(int v:edge[u]){
            if(v==p) continue;
            int a=Move(v);
            res|=(1LL<<num[v])*a;cal(v,u);
        }
        if(p!=-1) Move(p);
    };
    function<void()> solve = [&](){
        for(int i=0;i<N;i++) edge[i].clear();
        for(auto &[u,v]:pp) edge[u].push_back(v),edge[v].push_back(u);
        res|=(1LL<<num[P])*V;
        cal(P,-1);
    };
    function<void(int,int)> dfs2 = [&](int u,int p){
        pii del={-1,-1},add={-1,-1};
        if(num[u]==-1){
            for(int i=0;i<(int)pp.size();i++){
                int v1=pp[i].fi,v2=pp[i].se;
                if(deg[v1]==1 && v1!=p){
                    num[u]=num[v1];del=pp[i];
                    pp.erase(pp.begin()+i);break;
                }
                else if(deg[v2]==1 && v2!=p){
                    num[u]=num[v2];del=pp[i];
                    pp.erase(pp.begin()+i);break;
                }
            }
            deg[del.fi]--;deg[del.se]--;
            pp.push_back({p,u});add={p,u};
            deg[p]++;deg[u]++;
        }
        if(u==P) solve();
        for(int v:adj[u]) dfs2(v,u);
        if(del.fi!=-1){
            deg[add.fi]--;deg[add.se]--;
            for(int i=0;i<(int)pp.size();i++){
                if(pp[i]==add){pp.erase(pp.begin()+i);break;}
            }
            pp.push_back(del);
            deg[del.fi]++;deg[del.se]++;
        }
    };
    dfs2(0,0);
    return res;
}
