#include <bits/stdc++.h>
using namespace std;



vector<int> paint(int n, vector<pair<int,int>> E, int T) {
    int m=(int)E.size();
    vector<int> col(m);

    vector<vector<int>> G(n+1);
    for(auto [u,v]:E) G[u].push_back(v),G[v].push_back(u);
    
    vector<int> d(n+1,-1);
    {
        queue<int> q;
        q.push(T),d[T]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:G[u]) if(d[v]==-1) q.push(v),d[v]=d[u]+1;
        }
    }

    auto cost = [&](int x,int y){
        if(x>y) swap(x,y);
        return x*(n+1)+y;
    };
    auto dd = [&](int x,int y){
        return max(d[x],d[y]);
    };

    vector<int> ord(m);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        pair<int,int> vx = {dd(E[x].first,E[x].second),cost(E[x].first,E[x].second)};
        pair<int,int> vy = {dd(E[y].first,E[y].second),cost(E[y].first,E[y].second)};
        return vx>vy;
    });

    vector<int> sz(n+1,1);
    for(int id:ord){
        auto [x,y]=E[id];
        if(x>y) swap(x,y);
        if(d[x]<d[y] || (d[x]==d[y] && sz[x]>sz[y])){
            col[id]=0;
            sz[x]+=sz[y];
            sz[y]=0;
        }
        else{
            col[id]=1;
            sz[y]+=sz[x];
            sz[x]=0;
        }
    }

    return col;
}

int travel(int n, int u, vector<pair<int,int>> G) {
    auto cost = [&](int x,int y){
        if(x>y) swap(x,y);
        return x*(n+1)+y;
    };

    int x=-1,mx=-1;
    for(auto [v,c]:G){
        if((u<v)==c){
            int val=cost(u,v);
            if(val>mx) mx=val,x=v;
        }
    }
    return x;
}