#include "Azer.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

namespace A{
    const int inf=(1<<20)-1;
    int N,cnt=0,pu=0,pv=0,cur=0,lst=0;
    vector<bool> used;
    vector<int> dist;
    vector<vector<pii>> edge;
    void d(int u){
        used[u]=true;lst=dist[u];
        for(pii v:edge[u]) dist[v.first]=min(dist[v.first],dist[u]+v.second);
    }
    void Send(){
        int u=-1;
        for(int i=0;i<N;i++) if(!used[i] && (u==-1 || dist[i]<dist[u])) u=i;
        if(u==-1) return;
        int x=min(dist[u]-lst,501);pu=u;
        for(int i=0;i<9;i++) SendA((x>>i)&1);
    }
    void Receive(bool x){
        if(cnt<9){
            if(x) cur|=(1<<cnt);
            if(++cnt==9){
                cur+=lst;
                if(dist[pu]<cur){
                    for(int i=0;i<11;i++) SendA((pu>>i)&1);
                    d(pu);Send();cnt=cur=0;
                }
                else pv=0;
            }
        }
        else{
            if(x) pv|=(1<<(cnt-9));
            if(++cnt==20){
                dist[pv]=min(dist[pv],cur);
                d(pv);Send();
                cnt=cur=0;
            }
        }
    }
}  // namespace

void InitA(int N, int A, vector<int> U, vector<int> V, vector<int> C) {
    A::N=N;
    A::used.resize(N);
    A::dist.assign(N,A::inf);
    A::edge.resize(N);
    for(int i=0;i<A;i++){
        A::edge[U[i]].push_back({V[i],C[i]});
        A::edge[V[i]].push_back({U[i],C[i]});
    }
    A::dist[0]=0;A::d(0);
    A::Send();
}

void ReceiveA(bool x) {
    A::Receive(x);
}

vector<int> Answer() {
  return A::dist;
}
