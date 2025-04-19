#include "conveyor.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int maxn=1e5+5;
vector<pii> edge[maxn];
int n,col[maxn],gt[maxn],dir[maxn],total[maxn];
void dfs(int u,int par){
    for(pii v:edge[u]){
        if(v.fi==par) continue;
        col[v.fi]=(col[u]+1)%3;
        dfs(v.fi,u);
    }
}
vector<int> z;
void cal(int d){
    vector<int> x(n-1,0),y(n,0);
    for(int i=0;i<n;i++){
        if(col[i]==d){
            y[i]=1;
            for(pii v:edge[i]) x[abs(v.se)-1]=(v.se>0)^dir[abs(v.se)];
        }
    }
    z=Query(x,y);
    for(int i=0;i<n;i++){
        if(col[i]==d){
            if(z[i]){
                for(pii v:edge[i]){
                    gt[abs(v.se)]=1;
                    dir[abs(v.se)]=x[abs(v.se)-1]^(v.se>0);
                }
            }
            else{
                bool dn=false;
                for(pii v:edge[i]){
                    if(z[v.fi] && col[v.fi]==(d+1)%3){
                        dn=true;gt[abs(v.se)]=1;
                        dir[abs(v.se)]=x[abs(v.se)-1]^(v.se<0);
                    }
                }
                if(!dn){
                    for(pii v:edge[i]){
                        if(z[v.fi] && col[v.fi]==(d+2)%3){
                            gt[abs(v.se)]=1;
                            dir[abs(v.se)]=x[abs(v.se)-1]^(v.se<0);
                        }
                    }
                }
            }
        }
    }
}
void Solve(int N, std::vector<int> A, std::vector<int> B) {
    n=N;
    for(int i=0;i<n-1;i++){
        edge[A[i]].push_back({B[i],i+1});
        edge[B[i]].push_back({A[i],-i-1});
    }
    dfs(0,0);
    while(true){
        bool ok=true;
        for(int i=1;i<n;i++){
            if(!gt[i]) ok=false;
        }
        if(ok) break;
        total[0]=total[1]=total[2]=0;
        for(int i=0;i<n;i++){
            bool df=false;
            for(pii v:edge[i]){
                if(gt[abs(v.se)]==0) df=true;
            }
            total[col[i]]+=df;
        }
        //cout << total[0] << ' ' << total[1] << ' ' << total[2] << '\n';
        int d=max({total[0],total[1],total[2]}),pos=-1;
        for(int i=0;i<=2;i++){
            if(total[i]==d){pos=i;break;}
        }
        cal(pos);
    }
    vector<int> ans(n-1);
    for(int i=0;i<n-1;i++) ans[i]=dir[i+1];
    Answer(ans);
}

