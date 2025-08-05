#include "robot.h"
#include<bits/stdc++.h>
using namespace std;
const int N = 15;
int dx[]={1,-1,0,0},
    dy[]={0,0,1,-1};

array<int,5> f[N][N][N][N];    

void construct_instructions(std::vector<std::vector<bool>> g, int Q, int A, int B, int C, int D) {
    int n=(int)g.size(),m=(int)g[0].size();

    auto out = [&](int x,int y){
        return (x<0 || y<0 || x>=n || y>=m || g[x][y]);
    };

    for(int a=0;a<n;a++) for(int b=0;b<m;b++) for(int c=0;c<n;c++) for(int d=0;d<m;d++) f[a][b][c][d]={-1,-1,-1,-1,-1};
    queue<array<int,4>> q;
    q.push({A,B,C,D});
    f[A][B][C][D]={-2,-2,-2,-2,-2};
    while(!q.empty()){
        auto [a,b,c,d]=q.front();q.pop();
        for(int t=0;t<4;t++){
            int na=a+dx[t],nb=b+dy[t],nc=c+dx[t],nd=d+dy[t];
            if(out(na,nb)) na=a,nb=b;
            if(out(nc,nd)) nc=c,nd=d;
            if(f[na][nb][nc][nd][0]==-1){
                q.push({na,nb,nc,nd});
                f[na][nb][nc][nd]={a,b,c,d,t};
            }
        }
    }
    
    A=B=C=D=0;
    vector<int> ins;
    while(f[A][B][C][D][0]!=-2){
        auto [a,b,c,d,t]=f[A][B][C][D];
        ins.push_back(t);
        A=a,B=b,C=c,D=d;
    }
    reverse(ins.begin(),ins.end());
    for(int t:ins){
        if(t==0) down();
        else if(t==1) up();
        else if(t==2) right();
        else left();
    }
}
