#include "stations.h"
#include <bits/stdc++.h>
using namespace std;

std::vector<int> label(int n, int k, std::vector<int> U, std::vector<int> V) {
	std::vector<int> labels(n);
    vector<vector<int>> edge(n);
    for(int i=0;i<n-1;i++){
        edge[U[i]].push_back(V[i]);
        edge[V[i]].push_back(U[i]);
    }
    int num=0;
    function<void(int,int,int)> dfs;
    dfs = [&](int u,int p,int d){
        if(d==0) labels[u]=num++;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u,d^1);
        }
        if(d==1) labels[u]=num++;
    };
    dfs(0,-1,0);
	return labels;
}

int find_next_station(int s, int t, std::vector<int> c){
    sort(c.begin(),c.end());
    if(c.back()<s){
        c.push_back(s);
        for(int i=1;i<(int)c.size()-1;i++){
            if(t>=c[i] && t<c[i+1]) return c[i];
        }
        return c.front();
    }
    else{
        if(t>s && t<=c[0]) return c[0];
        for(int i=1;i<(int)c.size();i++){
            if(t>c[i-1] && t<=c[i]) return c[i];
        }
        return c.back();
    }
}
