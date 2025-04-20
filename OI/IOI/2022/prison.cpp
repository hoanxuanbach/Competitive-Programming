#include "prison.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> devise_strategy(int N) {
    vector<vector<int>> s(21,vector<int>(N+1,0));
    auto dnc = [&](auto &&dnc,int l,int r,int L,int R,int t,int id,int sz){
        if(l>r) return;
        l++;r--;
        s[id][0]=t;
        for(int i=L;i<=R;i++) if(i<l || r<i) s[id][i]=-((r<i)^t)-1;
        int S=r-l+1,k=min(S,2+(S>4)),d=ceil(1.0*S/k);
        for(int x=l,i=1;i<=k;i++){
            int y=min(r,x+d-1);
            for(int j=x;j<=y;j++) s[id][j]=sz+i;
            dnc(dnc,x,y,l-1,r+1,t^1,sz+i,sz+k);
            x=y+1;
        }
    };
    dnc(dnc,1,N,1,N,0,0,0);
    return s;
}
