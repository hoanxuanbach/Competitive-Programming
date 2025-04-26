#include "grid_encoding.h"
#include <bits/stdc++.h>
using namespace std;

void send(std::vector<std::vector<int>> A){
    int N=(int)A.size();
    vector<pair<int,int>> ord(N);
    for(int i=0;i<N;i++){
        ord[i].second=i;
        for(int j=0;j<N;j++) ord[i].first+=A[i][j];
    }
    sort(ord.begin(),ord.end());
    
    vector<int> mask(N);
    vector<vector<int>> f,g;
    for(int i=0;i<N;i++){
        int id=ord[i].second;

        vector<int> add;
        for(int j=0;j<N;j++){
            if(A[id][j] && !mask[j]) add.push_back(j);
        }
        if(add.empty()){
            if(!f.empty()) f.back().push_back(id);
        }
        else{
            g.push_back(add);
            f.push_back({id});
        }
        mask=A[id];
    }
    int sz=(int)f.size();
    for(int i=0;i<sz;i++){
        if(i) select(f[i-1][0],g[i][0]);
        for(int x:g[i]) select(f[i][0],x);
        for(int j=1;j<(int)f[i].size();j++) select(f[i][j],g[i][0]);
    }
}


std::vector<std::vector<int>> reconstruct(std::vector<std::vector<int>> B){
    int N=(int)B.size();
    
    vector<pair<int,int>> f(N,pair<int,int>{-1,-1});
    vector<vector<int>> A(N,vector<int>(N,-1));
    vector<int> zero(N,-1);
    for(int i=0;i<N;i++){
        int cnt=0;
        for(int j=0;j<N;j++){
            cnt+=(B[i][j]!=-1);
            if(B[i][j]==0) zero[i]=j;
        }
        for(int j=0;j<N;j++) if(B[i][j]==1) f[j]=max(f[j],{cnt,i});
        if(cnt==0){
            for(int j=0;j<N;j++) A[i][j]=0;
        }
    }
    vector<int> ord;
    for(int i=0;i<N;i++) if(f[i].second!=-1) ord.push_back(f[i].second);
    sort(ord.begin(),ord.end());
    ord.erase(unique(ord.begin(),ord.end()),ord.end());

    vector<int> cur;
    for(int id:ord){
        bool lst=true;
        for(int j=0;j<N;j++) if(B[id][j]==0) lst=false;
        if(lst) cur.push_back(id);
    }
    
    while(true){
        bool add=false;
        for(int x:ord){
            int i=zero[x];
            if(i==-1) continue;
            if(B[x][i]==0 && B[cur.back()][i]==1) cur.push_back(x),add=true; 
        }
        if(!add) break;
    }

    vector<int> mask(N,0);
    while(!cur.empty()){
        int id=cur.back();cur.pop_back();
        for(int i=0;i<N;i++) if(B[id][i]==1) mask[i]=1;
        for(int i=0;i<N;i++) if(B[id][i]==1){
            for(int j=0;j<N;j++) if(B[j][i]==1) A[j]=mask;
        }
    }
    return A;
}
