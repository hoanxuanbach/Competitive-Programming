#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;

int construct(std::vector<std::vector<int>> p) {
	int n = (int)p.size();
	std::vector<std::vector<int>> b(n,vector<int>(n,0));
    vector<int> vis0(n,0),vis1(n,0),v0,v1;
    function<void(int)> dfs0 = [&](int u){
        vis0[u]=1;v0.push_back(u);
        for(int i=0;i<n;i++){
            if(p[u][i]==0 || vis0[i]) continue;
            dfs0(i);
        }
    };
    function<void(int)> dfs1 = [&](int u){
        vis1[u]=1;v1.push_back(u);
        for(int i=0;i<n;i++){
            if(p[u][i]!=1 || vis1[i]) continue;
            dfs1(i);
        }
    };
    for(int i=0;i<n;i++){
        if(!vis0[i]){
            v0.clear();dfs0(i);
            for(int x:v0){
                for(int y:v0) if(p[x][y]!=1 && p[x][y]!=2) return 0;
            }
            vector<int> pre,cycle;
            for(int u:v0){
                if(!vis1[u]){
                    v1.clear();dfs1(u);
                    for(int x:v1){
                        for(int y:v1) if(p[x][y]!=1) return 0;
                    }
                    for(int j=1;j<(int)v1.size();j++){
                        int x=v1[j-1],y=v1[j];
                        b[x][y]=b[y][x]=1;
                    }
                    for(int x:v1){
                        for(int y:pre) if(p[x][y]!=2) return 0;
                    }
                    for(int x:v1) pre.push_back(x);
                    cycle.push_back(v1[0]);
                }
            }
            int sz=(int)cycle.size();
            if(sz==2) return 0;
            else if(sz>2){
                for(int j=0;j<sz;j++) b[cycle[j]][cycle[(j+1)%sz]]=b[cycle[(j+1)%sz]][cycle[j]]=1;
            }
        }
    }
	build(b);
	return 1;
}
