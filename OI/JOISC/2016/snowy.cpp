#include "snowy.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

namespace{
    const int maxn = 505;
    int n;
    vector<int> ver;
    vector<pii> edge[maxn];
    int dep[maxn],pid[maxn],ind[maxn],cnt[maxn],par[maxn];
}

void InitAnya(int N, int A[] , int B[]) {
    n=N;ver.clear();
    for(int i=0;i<N;i++) edge[i].clear();
    for(int i=0;i<N-1;i++){
        edge[A[i]].push_back({B[i],i});
        edge[B[i]].push_back({A[i],i});
    }
    function<int(int,int)> dfs = [&](int u,int p){
        for(auto [v,id]:edge[u]) if(v!=p){
            pid[v]=id;par[v]=u;
            dep[u]=max(dep[u],(dfs(v,u)+1)%10);
        }
        //cout << u << ' ' << dep[u] << ' ' << par[u] << ' ' << pid[u] << '\n';
        if(dep[u]==9){
            ind[u]=(int)ver.size();
            ver.push_back(u);
        }
        return dep[u];
    };
    par[0]=-1;
    dfs(0,-1);
}

void Anya(int C[]) {
    cnt[0]=0;
    for(int i=1;i<n;i++) Save(i,C[pid[i]]);
    function<void(int,int)> dfs = [&](int u,int p){
        for(auto [v,id]:edge[u]) if(v!=p){
            cnt[v]=cnt[u]+C[id];
            dfs(v,u);
        }
    };
    dfs(0,0);
    for(int i=0;i<(int)ver.size();i++){
        for(int j=0;j<9;j++) Save(n+9*i+j,cnt[ver[i]]>>j&1);
    }
}

void InitBoris(int N, int A[] , int B[]) {
    n=N;ver.clear();
    for(int i=0;i<N;i++) edge[i].clear();
    for(int i=0;i<N-1;i++){
        edge[A[i]].push_back({B[i],i});
        edge[B[i]].push_back({A[i],i});
    }
    function<int(int,int)> dfs = [&](int u,int p){
        for(auto [v,id]:edge[u]) if(v!=p){
            pid[v]=id;par[v]=u;
            dep[u]=max(dep[u],(dfs(v,u)+1)%10);
        }
        if(dep[u]==9){
            ind[u]=(int)ver.size();
            ver.push_back(u);
        }
        return dep[u];
    };
    par[0]=-1;
    dfs(0,-1);
}

int Boris(int u){
    int cnt=0;
    while(u!=-1 && dep[u]!=9){
        cnt+=Ask(u);
        u=par[u];
    }
    if(u!=-1){
        int x=ind[u];
        for(int i=0;i<9;i++) cnt+=Ask(n+9*x+i)<<i;
    }
    return cnt;
}
