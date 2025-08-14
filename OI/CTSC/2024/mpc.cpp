#include "mpc.h"
#include<bits/stdc++.h>
using namespace std;
const int B=8,C=4;

int n,m;
int precalc(int _n,int _m){
    n=_n,m=_m;
    return n+m+3;
}

bool transmit(player &P,int R,int I){
    int k=R-I-1,x=P.last_message;
    if(k<0){
        if(k>=-B) k+=m+C;
        else k+=m+B+11;
    }
    if(k<0) return 0;
    if(x){
        x=k;
        while(P.memory[x]) P.memory[x++]=0;
        P.memory[x]=1;
    }
    x=P.memory[k];
    if(I<n) P.memory[k]=0;
    return x;
}