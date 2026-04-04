#include<bits/stdc++.h>
using namespace std;

namespace A{
    int X,T;
}

void InitA(int _T, int _X) {
    A::X=_X;
    A::T=-2;
}

int GameA(int I, int J) {
    if(I==4) return -1;
    if(I!=2) return (J==4?-3:-4);
    int d=abs(A::T)&1;
    if(A::T>=0) d=(A::X>>A::T&1);
    A::T++;
    return (d?-1:-2);
}

namespace B{
    int X,T,K;
    bool flag;
}

void InitB(int T) {
    B::X=0;
    B::T=0;
    B::K=-1;
    B::flag=false;
}

int GameB(int I, int J) {
    if(I==4) return -1;
    if(I==2) return (J==4?-3:-4);
    int d=(I==1);
    if(B::flag){
        B::X+=d<<B::T;B::T++;
        if(B::T==30) return B::X;
    }
    else if(B::K==0 && d==1) B::flag=true;
    B::K=d;
    return (d?-2:-1);
}
