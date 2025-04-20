#include "grader.h"
#include<bits/stdc++.h>

int HC(int N){
    std::function<int(int)> f = [&](int n){
        return (n<5?1:(n+1>>1)-f(n>>1));
    };
    int l=1,r=N,w=log(3*N)/log(2);
    while(l<r){
        if(r==2){
            Guess(1);
            return (Guess(2)<0?1:2);
        }
        int s=(2<<(w-2))/3+2-(w&1);
        int y=(r==N)?s+f(r-s):2*s-1,x=2*s-y;
        Guess(x);
        int k=Guess(y);
        if(k==-1) r=x+y-1>>1;
        else if(k==0) return x+y>>1;
        else{
            l=x+y+2>>1;x=y;
            while(l<r){
                y=((l+r)>>1<<1)-x;
                if(x==y) y++;
                y=std::min(N,std::max(y,1));
                k=Guess(y);
                if(k==0) return x+y>>1;
                else if((k==1)^(x>y)) l=x+y+2>>1;
                else r=x+y-1>>1;
                x=y;
            }
        }
        w-=2;
    }
    return l;
}
