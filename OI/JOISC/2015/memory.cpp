#include "Memory_lib.h"
#include <bits/stdc++.h>
using namespace std;

int f(int N,int col,int pos,int lst,int val){
    return col*(N+2)*(N+2)*(N+2)+val*(N+2)*(N+2)+lst*(N+2)+pos;
}

int Memory(int N, int M) {
    if(M==0) return f(N,0,1,1,0);
    int pos=M%(N+2);M/=(N+2);
    int lst=M%(N+2);M/=(N+2);
    int val=M%(N+2);M/=(N+2);
    //cout << pos << ' ' << lst << ' ' << val << ' ' << M << '\n';
    if(M>=2 || pos==0) return 0;
    if(pos==N+1) return -1;
    if(pos==lst){
        if(val!=0 || M!=0) return 0;
        char c=Get(lst);
        if(c=='>' || c==']') return f(N,(c=='>'),pos,pos-1,1);
        else return f(N,(c=='<'),pos,pos+1,1);
    }
    else if(pos<lst){
        if(lst==N+1) return -2;
        char c=Get(lst);
        if(c=='<' || c=='[') val++;
        else val--;
        if(val<0) return 0;
        else if(val==0){
            if(M!=(c=='>')) return -2;
            else return f(N,0,pos+1,pos+1,0);
        }
        else return f(N,M,pos,lst+1,val);
    }
    else{
        if(lst==0) return -2;
        char c=Get(lst);
        if(c=='>' || c==']') val++;
        else val--;
        if(val<0) return 0;
        else if(val==0){
            if(M!=(c=='<')) return -2;
            else return f(N,0,pos+1,pos+1,0);
        }
        else return f(N,M,pos,lst-1,val);
    }
}
