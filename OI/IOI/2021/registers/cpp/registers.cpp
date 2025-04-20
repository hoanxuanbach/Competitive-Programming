#include "registers.h"
#include<bits/stdc++.h>
using namespace std;
const int ALL = 99;
const int ONE = 98;
const int ALT = 97;
const int B = 2000;

void construct_instructions(int s, int n, int k, int q) {
    vector<bool> v(B);
    for(int i=0;i<B;i+=2*k) v[i]=1;
    append_store(ONE,v);
    for(int i=0;i+k<=B;i+=2*k) for(int j=0;j<k;j++) v[i+j]=1;
    append_store(ALT,v);
    for(int i=0;i<B;i++) v[i]=(i>=n*k);
    append_store(ALL,v);
    append_or(0,0,ALL);

    auto f = [&](int d){
        if(!s) append_right(1,0,d);
        append_and(1,1,ALT);
        append_and(0,0,ALT);
        append_not(2,1);
        append_add(2,0,2);
        append_right(2,2,k);
        append_and(2,2,ONE);
        append_add(2,2,ALT);
        append_not(3,2);
        append_and(5,1,2);
        append_and(6,0,3);
        if(!s) return append_or(0,5,6);
        append_or(6,5,6);
        append_and(3,1,3);
        append_and(2,0,2);
        append_or(3,2,3);
    };
    if(!s){
        int d=k;
        while(n>1) f(d),d<<=1,n=(n+1)/2;
        return;
    }
    for(int i=0;i<n;i++){
        if(i&1) append_left(1,0,k);
        else append_right(1,0,k);
        f(k);
        if(i&1) append_right(6,6,k);
        else append_left(3,3,k);
        append_or(0,3,6);
    }
}
