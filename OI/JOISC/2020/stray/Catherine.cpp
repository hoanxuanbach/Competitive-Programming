#include "Catherine.h"
#include <bits/stdc++.h>
using namespace std;

namespace {
    int A,B,p=-1;
    int up=0,st=0,num=0;
    int f[81];
}  // namespace

void Init(int A, int B) {
    ::A = A;
    ::B = B;
    for(int i=0;i<81;i++) f[i]=-2;
    f[39]=-1;f[43]=0;f[32]=-1;f[13]=1;
    f[16]=-1;f[31]=0;f[67]=-1;f[64]=1;

}

int Move(std::vector<int> y) {
    auto g = [&](int val){return p=(val==-1?p:val),val;};
    if(A==2){
        int d=y[0]+y[1]+(st!=0);st++;
        if(up) return g(d>=3?(p^1):y[1]);
        if(d==1) return up=true,g(st!=1?-1:y[1]);
        if(d>2) return up=true,g(y[0]==0 || y[1]==0?-1:(y[1]+(p==1)>y[0]+(p==0)?0:1));
        num=num*3+y[1]+(p==1);
        if(st<=3) return g(!y[0]);
        else return up=true,g(f[num]);
    }
    else for(int i=0;i<3;i++) if(y[i] && !y[(i+2)%3]) return i;
    return -2;
}
