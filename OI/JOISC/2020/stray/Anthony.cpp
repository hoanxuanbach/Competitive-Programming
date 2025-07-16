#include "Anthony.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
namespace {
    int c[]={0,1,0,0,1,1};

}  // namespace

vector<int> Mark(int N, int M, int A, int B,
                      std::vector<int> U, std::vector<int> V) {
    vector<int> X(M),dep(N,-1);
    vector<vector<pii>> edge(N);
    for(int i=0;i<M;i++) edge[U[i]].push_back({V[i],i}),edge[V[i]].push_back({U[i],i});
    queue<pii> q;q.push({0,0});dep[0]=0;
    while(!q.empty()){
        auto [u,d]=q.front();q.pop();
        for(auto [v,id]:edge[u]){
            if(B){
                if(dep[v]!=-1) continue;
                int nd=((int)edge[v].size()==2?(d+1)%6:(c[d]^1));
                q.push({v,dep[v]=nd});X[id]=c[d];
            }
            else if(dep[v]==-1) dep[v]=d+1,q.push({v,dep[v]});
        }
    }
    if(!B) for(int i=0;i<M;i++) X[i]=min(dep[U[i]],dep[V[i]])%3;
    return X;
}
