#include"communication.h"
#include<bits/stdc++.h>
using namespace std;

struct seg{
    int sz;
    vector<array<int,2>> S; 
    seg(int s=0):sz(s){}
    seg(int l,int r):sz(r-l+1){S.push_back({l,r});}
    pair<seg,seg> split(int d){
        int ss=(sz+d)/2;
        seg L(ss),R(sz-ss);
        int cnt=0;
        for(auto [l,r]:S){
            if(cnt==ss) R.S.push_back({l,r});
            else if(cnt+r-l+1<=ss) L.S.push_back({l,r}),cnt+=r-l+1;
            else{
                int m=l+ss-cnt;
                L.S.push_back({l,m-1});
                R.S.push_back({m,r});
                cnt=ss;
            }
        }
        return {L,R};
    }
    bool query(int x){
        for(auto &[l,r]:S) if(l<=x && x<=r) return true;
        return false;
    }
    vector<int> get(){
        vector<int> res;
        for(auto &[l,r]:S) for(int i=l;i<=r;i++) res.push_back(i);
        return res;
    }
};
seg merge(seg L,seg R){
    seg res(L.sz+R.sz);
    res.S=L.S;
    res.S.insert(res.S.end(),R.S.begin(),R.S.end());
    return res;
}

void encode(int N, int X) {
    seg A(1,N),B;
    while(A.sz+B.sz>3){
        seg lA,rA,lB,rB;
        tie(lA,rA)=A.split(0),tie(lB,rB)=B.split(1);
        int bit=-1;
        if(lA.query(X) || lB.query(X)) bit=send(1);
        else bit=send(0);
        if(bit) A=merge(lA,lB),B=rA;
        else A=merge(rA,rB),B=lA;
    }
    vector<int> cur=merge(A,B).get();
    if((int)cur.size()<=2) return;
    if(cur[0]==X) send(0),send(0),send(0),send(0),send(0);
    else if(cur[1]==X) send(0),send(1),send(1),send(0);
    else send(1),send(1),send(1),send(1);
}

const int T[16] = {2, 2, 2, 2, 2, 1, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0};
std::pair<int, int> decode(int N) {
    seg A(1,N),B;
    while(A.sz+B.sz>3){
        seg lA,rA,lB,rB;
        tie(lA,rA)=A.split(0),tie(lB,rB)=B.split(1);
        if(receive()) A=merge(lA,lB),B=rA;
        else A=merge(rA,rB),B=lA; 
    }
    vector<int> cur=merge(A,B).get();
    if((int)cur.size()==1) return {cur[0],cur[0]};
    else if((int)cur.size()==2) return {cur[0],cur[1]};
    else{
        int s=0;
        for(int i=0;i<4;i++) s=s<<1|receive();
        if(T[s]==0) return {cur[1],cur[2]};
        else if(T[s]==1) return {cur[0],cur[2]};
        else return {cur[0],cur[1]};
    }
    return {-1,-1};
}