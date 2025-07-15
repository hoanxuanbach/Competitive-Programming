#include "koala.h"
#include<bits/stdc++.h>
using namespace std;

int B[105],R[105];

int minValue(int N, int W) {
    for(int i=0;i<N;i++) B[i]=0;
    B[0]=1;
    playRound(B,R);
    for(int i=0;i<N;i++) if(R[i]<=B[i]) return i;
    return 0;
}

int maxValue(int N, int W) {
    vector<int> ord(N);
    iota(ord.begin(),ord.end(),0);
    while((int)ord.size()>1){
        for(int i=0;i<N;i++) B[i]=0;
        for(int x:ord) B[x]=N/(int)ord.size();
        vector<int> nxt;
        playRound(B,R);
        for(int x:ord) if(R[x]>B[x]) nxt.push_back(x);
        swap(nxt,ord);
    }
    return ord[0];
}

int greaterValue(int N, int W) {
    vector<int> x(8);
    iota(x.begin(),x.end(),1);
    x.pop_back();x.back()++;
    int l=0,r=6;
    while(l<=r){
        int mid=(l+r)>>1,d=x[mid];
        for(int i=0;i<N;i++) B[i]=0;
        B[0]=B[1]=d;
        playRound(B,R);
        if(R[0]>d && R[1]<=d) return 0;
        else if(R[1]>d && R[0]<=d) return 1;
        if(R[0]<=d) r=mid-1;
        else l=mid+1;
    }
    return 0;
}

void allValues(int N, int W, int *P) {
    if (W == 2*N) {
        vector<int> ord(N);
        iota(ord.begin(),ord.end(),0);
        stable_sort(ord.begin(),ord.end(),[&](int x,int y){
            for(int i=0;i<N;i++) B[i]=0;
            B[x]=B[y]=N;
            playRound(B,R);
            return R[y];
        });
        for(int i=0;i<N;i++) P[ord[i]]=i+1;
    } else{
        int L=1;
        vector<int> ord(N);
        iota(ord.begin(),ord.end(),0);
        function<void(vector<int>)> dnc = [&](vector<int> p){
            if((int)p.size()==1){
                P[p[0]]=L++;
                return;
            }
            int D=min((int)sqrt(2*L),W/(int)p.size());
            for(int i=0;i<N;i++) B[i]=0;
            for(int x:p) B[x]=D;
            playRound(B,R);
            vector<int> lt,rt;
            for(int x:p){
                if(R[x]) rt.push_back(x);
                else lt.push_back(x);
            }
            dnc(lt);dnc(rt);
        };
        dnc(ord);
    }
}
