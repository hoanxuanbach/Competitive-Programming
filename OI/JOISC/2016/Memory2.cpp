#include "Memory2_lib.h"
#include<bits/stdc++.h>
using namespace std;

void Solve(int T, int N){
    vector<int> p(2*N,-1),cnt(N,0);
    vector<vector<int>> res(2*N,vector<int>(2*N,-1));
    auto query = [&](int i,int j){
        if(res[i][j]!=-1) return res[i][j];
        return res[i][j]=res[j][i]=Flip(i,j);
    };
    vector<int> cur={0,1};
    auto change = [&](){
        for(int x:cur){
            for(int y:cur){
                if(x==y) continue;
                for(int z:cur){
                    if(z==x || z==y) continue;
                    int a=query(x,y),b=query(x,z),c=query(y,z);
                    if(a==b && a!=c) p[x]=a;
                }
            }
        }
        vector<int> nw;
        for(int x:cur) if(p[x]==-1) nw.push_back(x);
        cur=nw;
    };
    for(int i=2;i<2*N;i++) cur.push_back(i),change();
    for(int i=0;i<2*N;i++) if(p[i]!=-1) cnt[p[i]]++;
    for(int i=0;i<N;i++) if(cnt[p[i]]!=2) cur.push_back(i);
    cnt.assign(N,0);change();
    int num=0;
    for(int i=0;i<2*N;i++) if(p[i]!=-1) cnt[p[i]]++;
    while(cnt[num]==2) num++;
    for(int i=0;i<2*N;i++) if(p[i]==-1) p[i]=num;
    vector<vector<int>> ans(N);
    for(int i=0;i<2*N;i++) ans[p[i]].push_back(i);
    for(int i=0;i<N;i++) Answer(ans[i][0],ans[i][1],i);
}
