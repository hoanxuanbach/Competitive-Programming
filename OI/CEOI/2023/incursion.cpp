#include "incursion.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 45005;

int n,sz[maxn];
vector<int> edge[maxn];

pair<int,int> find_centroid(){
    pair<int,int> pos={0,0};
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;
        bool ok=true;
        for(int v:edge[u]) if(v!=p){
            dfs(v,u);sz[u]+=sz[v];
            if(sz[v]*2>n) ok=false;
        }
        if((n-sz[u])*2>n) ok=false;
        if(ok){
            if(pos.first) pos.second=u;
            else pos.first=u;
        }
    };
    dfs(1,0);
    return pos;
}

int d[maxn],par[maxn];
void dfs_dist(int u,int p){
    d[u]=d[p]+1;
    for(int v:edge[u]) if(v!=p) dfs_dist(v,u);
}
void dfs(int u,int p){
    sz[u]=1,par[u]=p;
    for(int v:edge[u]) if(v!=p) dfs(v,u),sz[u]+=sz[v];
    if(p) edge[u].erase(find(edge[u].begin(),edge[u].end(),p));
}

std::vector<int> mark(std::vector<std::pair<int, int>> E, int T){
    n=(int)E.size()+1;
    for(int i=1;i<=n;i++) edge[i].clear();
    for(auto [u,v]:E) edge[u].push_back(v),edge[v].push_back(u);
    auto [A,B]=find_centroid();
    if(B){
        dfs_dist(T,0);
        if(d[B]<d[A]) swap(A,B);
    }
    dfs(A,0);
    vector<int> col(n);
    while(T) col[T-1]=1,T=par[T];
    return col;
}
void locate(std::vector<std::pair<int, int>> E, int S,int t){
    n=(int)E.size()+1;
    for(int i=1;i<=n;i++) edge[i].clear();
    for(auto [u,v]:E) edge[u].push_back(v),edge[v].push_back(u);
    auto [A,B]=find_centroid();
    
    dfs(A,0);
    while(!t) t=visit(S=(par[S]?par[S]:B));
    while(true){
        sort(edge[S].begin(),edge[S].end(),[&](int x,int y){return sz[x]>sz[y];});
        if(edge[S].empty()) return;
        bool check=false;
        for(int u:edge[S]){
            t=visit(u);
            if(t){S=u,check=true;break;}
            t=visit(S);
        }
        if(!check) break;
    }
}