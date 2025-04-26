#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

int findEgg (int N, vector <pair<int,int>> bridges)
{
    vector<vector<int>> edge(N+1);
    for(auto [u,v]:bridges){
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    vector<int> path;
    function<void(int,int)> dfs = [&](int u,int p){
        path.push_back(u);
        for(int v:edge[u]) if(v!=p) dfs(v,u);
    };
    dfs(1,0);
    int l=0,r=N-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(query(vector<int>(path.begin(),path.begin()+mid+1))) r=mid;
        else l=mid+1;
    }
    return path[l];
}
