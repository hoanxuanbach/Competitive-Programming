#include "telepathy.h"
#include<bits/stdc++.h>
using namespace std;

vector<int> build(int N){
    vector<int> ans;
    int l=0,r=0,dir=1;
    double len=1;

    while((int)ans.size()<10*N){
        if(dir){
            int nr=(int)len;
            for(int i=l+1,pre=l;i<=r+1;i++) if((i&1) || (i==r+1)) ans.push_back({i-pre}),pre=i;
            for(int i=r+2;i<=nr;i++) ans.push_back(1);
            r=nr;
        }
        else{
            int nl=-(int)len;
            for(int i=r-1,pre=r;i>=l-1;i--) if(!(i&1) || (i==l-1)) ans.push_back({i-pre}),pre=i;
            for(int i=l-2;i>=nl;i--) ans.push_back(-1);
            l=nl;
        }
        len*=1.685;dir^=1;
    }
    ans.resize(10*N);
    return ans;
}

std::vector<int> Aitana(int N, std::vector<int> A, std::vector<int> B, int S,
                        int subtask) {
    
    
    vector<int> delta=build(N);
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++) g[A[i]].push_back(B[i]),g[B[i]].push_back(A[i]);
    vector<int> root;

    vector<int> sz(N);
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;
        int mx=0;
        for(int v:g[u]) if(v!=p){
            dfs(v,u);
            sz[u]+=sz[v];
            mx=max(mx,sz[v]);
        }
        mx=max(mx,N-sz[u]);
        if(mx<=(N/2)) root.push_back(u);
    };
    dfs(0,-1);

    vector<int> par(N);
    function<void(int,int)> dfs2 = [&](int u,int p){
        par[u]=p;
        for(int v:g[u]) if(v!=p) dfs2(v,u);
    };
    dfs2(root[0],-1);

    vector<int> path;
    vector<int> ans={S};
    
    while(S!=-1) path.push_back(S),S=par[S];

    int pos=0;
    for(int x:delta){
        if(x>0) pos++;
        if(x==-2) pos--;
        ans.push_back(path[max(0,min(pos,(int)path.size()-1))]);
    }

    for(int i=1;i<10*N;i++) if(ans[i-1]==root[0] && ans[i+1]==root[0] && (int)root.size()>1) ans[i]=root[1];
    return ans;
}

std::vector<int> Bruno(int N, std::vector<int> A, std::vector<int> B, int S,
                       int subtask) {
    
    vector<int> delta=build(N);
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++) g[A[i]].push_back(B[i]),g[B[i]].push_back(A[i]);
    vector<int> root;

    vector<int> sz(N);
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;
        int mx=0;
        for(int v:g[u]) if(v!=p){
            dfs(v,u);
            sz[u]+=sz[v];
            mx=max(mx,sz[v]);
        }
        mx=max(mx,N-sz[u]);
        if(mx<=(N/2)) root.push_back(u);
    };
    dfs(0,-1);

    vector<int> par(N);
    function<void(int,int)> dfs2 = [&](int u,int p){
        par[u]=p;
        for(int v:g[u]) if(v!=p) dfs2(v,u);
    };
    dfs2(root[0],-1);

    vector<int> path;
    vector<int> ans={S};
    while(S!=-1) path.push_back(S),S=par[S];


    int pos=0;
    for(int x:delta){
        if(x<0) pos++;
        if(x==2) pos--;
        ans.push_back(path[max(0,min(pos,(int)path.size()-1))]);
    }
    return ans;

}
