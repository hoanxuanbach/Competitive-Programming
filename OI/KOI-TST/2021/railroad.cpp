#include "railroad.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

std::vector<pii> encode_map(int N, int K, int &X, std::vector<pii> E) {
    vector<pii> res;
    vector<vector<int>> edge(N+1);
    for(auto [u,v]:E){
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    X=-1;
    for(int i=1;i<=N;i++){
        int total=0;
        vector<int> cnt(N,0);
        function<void(int,int,int)> dfs = [&](int u,int p,int d){
            total+=cnt[d];cnt[d]++;
            for(int v:edge[u]) if(v!=p) dfs(v,u,d+1);
        };
        dfs(i,0,0);
        if(total>=K){
            X=i;
            break;
        }
    }
    vector<vector<int>> dd(N);
    function<void(int,int,int)> dfs2 = [&](int u,int p,int d){
        for(int i=0;i<min(K,(int)dd[d].size());i++){
            if((int)res.size()==K) break;
            res.push_back({u,dd[d][i]});
        }
        dd[d].push_back(u);
        for(int v:edge[u]) if(v!=p) dfs2(v,u,d+1);
    };
    dfs2(X,0,0);
	return res;
}

std::vector<std::pair<int, int> > decode_map(int N, int K, int X, std::vector<std::pair<int, int> > E) {
	vector<pii> res;
    vector<vector<int>> edge(N+1);
    vector<bool> check(N+1,false);
    for(auto [u,v]:E){
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    vector<int> cur={X};
    while(!cur.empty()){
        vector<int> nxt;
        for(int u:cur) check[u]=true;
        for(int u:cur){
            for(int v:edge[u]){
                if(!check[v]){
                    res.push_back({u,v});
                    nxt.push_back(v);
                }
            }
        }
        swap(nxt,cur);
    }
    return res;
}
