#include "jumps.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
const int maxl = 20;

int N,H[maxn],P[maxn],lt[maxn],rt[maxn];
int jmp[maxn][maxl],nxt[maxn][maxl],Max[maxn][maxl];

void init(int _N, vector<int> _H) {
    N=_N;
    for(int i=0;i<N;i++){
        H[i+1]=_H[i];
        P[H[i+1]]=i+1;
    }
    vector<int> v;
    for(int i=1;i<=N;i++){
        while(!v.empty() && H[v.back()]<H[i]) v.pop_back();
        rt[i]=(v.empty()?0:v.back());
        v.push_back(i);
    }
    v.clear();
    for(int i=N;i>=1;i--){
        while(!v.empty() && H[v.back()]<H[i]) v.pop_back();
        jmp[i][0]=lt[i]=(v.empty()?0:v.back());
        v.push_back(i);
        nxt[i][0]=(H[rt[i]]>H[lt[i]]?rt[i]:lt[i]);
        Max[i][0]=H[i];
    }
    for(int i=1;i<18;i++){
        for(int j=1;j<=N;j++){
            jmp[j][i]=jmp[jmp[j][i-1]][i-1];
            nxt[j][i]=nxt[nxt[j][i-1]][i-1];
        }
        for(int j=1;j<=N-(1<<i)+1;j++) Max[j][i]=max(Max[j][i-1],Max[j+(1<<(i-1))][i-1]);
    }
}

int dist(int l,int r){
    int cnt=0;
    for(int i=17;i>=0;i--){
        if(!jmp[l][i]) continue;
        if(jmp[l][i]<=r){
            cnt+=(1<<i);
            l=jmp[l][i];
        }
    }
    return cnt;
}

int query(int l,int r){
    int res=0;
    for(int i=0;i<18;i++) if((r-l+1)>>i&1){
        res=max(res,Max[l][i]);
        l+=(1<<i);
    }
    return res;
}
int get(int l,int r,int x){
    int res=0;
    for(int i=17;i>=0;i--){
        if((r-l+1)<(1<<i)) continue;
        int val=Max[r-(1<<i)+1][i];
        if(val>x) continue;
        res=max(res,val);
        r-=(1<<i);
    }
    return res;
}

int minimum_jumps(int A, int B, int C, int D) {
    A++;B++;C++;D++;
    int x=P[query(C,D)];
    int p=P[get(A,B,H[x])];
    if(!p) return -1;
    int m=P[query(p,C-1)];
    if(H[m]>H[x]) return -1;
    int l=lt[m],cnt=0;
    for(int i=17;i>=0;i--){
        int cc=nxt[p][i];
        if(!cc) continue;
        if(H[cc]<H[l]) cnt+=(1<<i),p=cc;
    }
    int val=dist(p,l);
    int r=rt[p];
    if(r && H[r]<H[x] && H[r]>H[l]) val=min(val,2);
    return cnt+val;
}
