#include "Broken_device_lib.h"
#include<bits/stdc++.h>
using namespace std;

void Anna( int N, long long X, int K, int P[] ){
    //cout << '*' << N << ' ' << X << ' ' << K << '\n';
    vector<int> d(N,0);
    for(int i=0;i<K;i++) d[P[i]]=1;
    for(int i=N-3;i>=0;i-=3){
        int a=0,b=0,c=0;
        if(d[i]+d[i+1]+d[i+2]==0){
            if(X%4==0) b=1;
            else a=1,b=X>>1&1,c=X&1;
            X/=4;
        }
        else if(d[i]+d[i+1]+d[i+2]==1){
            if(X&1){
                if(d[i]) b=c=1;
                else a=1;
            }
            else if(d[i+2]) a=X>>1&1,b=1,X/=2;
            else c=1;
            X/=2;
        }
        Set(i,a);Set(i+1,b);Set(i+2,c);
        //cout << X << ' ' << a << b << c << '\n';
    }
}

long long Bruno( int N, int A[] ){
    long long res=0;
    for(int i=0;i<N;i+=3){
        int num=A[i]*4+A[i+1]*2+A[i+2];
        if(num==1) res*=2;
        else if(num==2) res*=4;
        else if(num>=5) res=res*4+num%4;
        else if(num>=3) res=res*2+1;
    }
    return res;
}
