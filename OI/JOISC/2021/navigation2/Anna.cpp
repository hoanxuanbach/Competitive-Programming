#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;

namespace A{
    const int Col = 13;
    const int maxn = 105;
    int flag[maxn][maxn];

    void solve(int N,int K,vector<int> R,vector<int> C){
        function<int(int,int,int,int)> g = [&](int i,int j,int x,int y){
            if(j<=y-2) return 9;
            if(j>=y+2) return 10;
            if(i<=x-2) return 11;
            if(i>=x+2) return 12;
            int val=(i-x+1)*3+j-y+1+1;
            return (val==9?-1:val);
        };
        function<bool(int)> f = [&](int d){
            for(int i=0;i<N;i++) for(int j=0;j<N;j++){
                int k=(i+(d/3))%3*3+(j+d%3)%3;
                flag[i][j]=(k<7?g(i,j,R[k],C[k]):(k==8?Col:0));
                if(flag[i][j]==-1) return false;
            }
            return true;
        };
        for(int i=0;i<9;i++) if(f(i)) break;
        vector<bool> used(Col+1,0);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) used[flag[i][j]]=true;
        }
        int x=0;
        while(used[x]) x++;
        for(int i=0;i<N;i++) for(int j=0;j<N;j++){
            if(flag[i][j]>x) flag[i][j]--;
            if(flag[i][j]==0) flag[i][j]=x;
            SetFlag(i,j,flag[i][j]);
        }
    }
}

void Anna(int N, int K, std::vector<int> R, std::vector<int> C) {
    A::solve(N,K,R,C);
}
