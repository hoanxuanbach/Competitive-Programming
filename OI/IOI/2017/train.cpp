#include "train.h"
#include<bits/stdc++.h>
using namespace std;

std::vector<int> who_wins(vector<int> A, std::vector<int> R, vector<int> U, vector<int> V) {
	int n=(int)A.size(),m=(int)U.size();
    vector<vector<int>> edge(n);
    for(int i=0;i<m;i++) edge[V[i]].push_back(U[i]);
    vector<int> res(n,1);
    auto f = [&](vector<int> c,int x){
        queue<int> q;
        vector<int> d(n);
        for(int i=0;i<n;i++) for(int v:edge[i]) if(res[i] && res[v]) d[v]++;
        for(int i=0;i<n;i++)  if(res[i] && c[i]) q.push(i);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:edge[u]){
                if(c[v] || !res[v]) continue;
                d[v]--;
                if(A[v]==x || !d[v]){
                    c[v]=1;
                    q.push(v);
                }
            }
        }
        return c;
    };
    while(true){
        for(int i=0;i<n;i++) if(!res[i]) R[i]=0;
        vector<int> S=f(R,1);
        int ok=1;
        for(int i=0;i<n;i++){
            if(!res[i]) continue;
            ok&=S[i];S[i]^=1;
        }
        if(ok) break;
        S=f(S,0);ok=1;
        for(int i=0;i<n;i++){
            if(!res[i]) continue;
            ok&=S[i];
            if(S[i]) res[i]=0;
        }
        if(ok) break;
    }
	return res;
}
