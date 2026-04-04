#include "voltage.h"
#include<bits/stdc++.h>
using namespace std;

bool solve(int N, int M) {
    vector<int> S(N,1);

    vector<int> empty(N,0);
    vector<int> X(N,1),Y(N,1);

    vector<pair<int,int>> E;

    queue<int> q;
    for(int i=0;i<N;i++){
        Y[i]=0;
        if(query(X,Y)==0) q.push(i);
        Y[i]=1;
    }

    while(!q.empty()){
        int u=q.front();q.pop();

        S[u]=0;

        vector<int> adj;
        while(true){
            
            X=Y=empty;X[u]=1;
            for(int v:adj) X[v]=Y[v]=1; 
            if(query(X,Y)==0) break;
            
            int l=0,r=N-1;
            while(l<r){
                int mid=(l+r)>>1;

                X=Y=empty;X[u]=1;
                for(int i=mid+1;i<N;i++) if(S[i]==1) X[i]=Y[i]=1;
                for(int v:adj) X[v]=Y[v]=1;

                if(query(X,Y)!=0) r=mid;
                else l=mid+1;
            }

            E.push_back({u,l});
            adj.push_back(l);
        }

        for(int v:adj){
            X=Y=S;Y[v]=0;
            if(query(X,Y)==0) q.push(v);
        }

    }

    for(int i=0;i<N;i++) if(S[i]==1) return false;
    for(auto [u,v]:E) answer(u,v);
    return true;
}
