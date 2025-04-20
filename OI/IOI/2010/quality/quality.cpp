#include "quality.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3005;
int s[maxn][maxn];
int query(int x,int y,int u,int v){
    return s[u][v]-s[x-1][v]-s[u][y-1]+s[x-1][y-1];
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
    auto check = [&](int x){
        for(int i=0;i<R;i++) for(int j=0;j<C;j++) s[i+1][j+1]=(Q[i][j]<=x?1:-1);
        for(int i=1;i<=R;i++) for(int j=1;j<=C;j++) s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
        for(int i=H;i<=R;i++) for(int j=W;j<=C;j++){
            if(query(i-H+1,j-W+1,i,j)>0) return true;
        }
        return false;
    };
    int l=1,r=R*C,res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
