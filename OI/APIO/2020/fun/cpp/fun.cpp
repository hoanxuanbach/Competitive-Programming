#include "fun.h"
#include <bits/stdc++.h>
using namespace std;
/*
int hoursRequired(int X, int Y);

int attractionsBehind(int X, int Y);
*/

std::vector<int> createFunTour(int N, int Q) {
    vector<int> P(N);
    int X=0,Min=N;
    for(int i=0;i<N;i++){
        int sz=attractionsBehind(0,i);
        if(sz>N/2 && sz<Min) X=i,Min=sz;
    }
    vector<int> D(N),cc;
    for(int i=0;i<N;i++){
        D[i]=hoursRequired(X,i);
        if(D[i]==1) cc.push_back(i);
    }
    int S=(int)cc.size();
    vector<vector<int>> G(S);
    for(int i=0;i<N;i++){
        if(i==X) continue;
        int j=0;
        while(j+1<S && hoursRequired(cc[j],i)+D[cc[j]]!=D[i]) j++;
        G[j].push_back(i);
    }
    for(int i=0;i<S;i++){
        sort(G[i].begin(),G[i].end(),[&](int x,int y){
            return D[x]<D[y];
        });
    }
    G.resize(S=3);
    int c=-1,T=0;
    vector<int> p={0,1,2};
    sort(p.begin(),p.end(),[&](int x,int y){return (int)G[x].size()>(int)G[y].size();});
    while((int)G[p[0]].size()<(int)G[p[1]].size()+(int)G[p[2]].size()){
        sort(p.begin(),p.end(),[&](int x,int y){return D[G[x].back()]>D[G[y].back()];});
        int i=(p[0]==c);
        P[T++]=G[p[i]].back();
        G[p[i]].pop_back();c=p[i];
        sort(p.begin(),p.end(),[&](int x,int y){return (int)G[x].size()>(int)G[y].size();});
    }
    G[p[1]].insert(G[p[1]].end(),G[p[2]].begin(),G[p[2]].end());
    sort(G[p[1]].begin(),G[p[1]].end(),[&](int x,int y){return D[x]<D[y];});
    int t=0;
    if(T>1 && D[P[T-1]]<D[G[p[1]].back()]) t^=1;
    while(!G[p[t]].empty()){
        P[T++]=G[p[t]].back();
        G[p[t]].pop_back();t^=1;
    }
    P[T++]=X;
    return P;
}
