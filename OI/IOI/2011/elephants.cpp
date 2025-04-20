#include "elephants.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 150005;
const int B = 500;

int N,L,S,V[maxn];
vector<vector<int>> X;
vector<vector<pii>> P;

void build(vector<int> &x,vector<pii> &p){
    int sz=(int)x.size();
    p.assign(sz,{0,0});
    int rt=sz;
    for(int i=sz-1;i>=0;i--){
        while(rt>0 && x[rt-1]>x[i]+L) rt--;
        if(rt==sz) p[i].fi=x[i];
        else p[i]=p[rt];
        p[i].se++;
    }
}

void init(int _N, int _L, int _X[])
{
    N=_N,L=_L;S=(N-1)/B+1;
    X.assign(S,{});P.assign(S,{});
    for(int i=0;i<N;i++) X[i/B].push_back(V[i]=_X[i]);
    for(int i=0;i<S;i++) build(X[i],P[i]);
}

void del(int val){
    int p=0;
    while(p<S && val>X[p].back()) p++;
    for(int i=0;i<(int)X[p].size();i++){
        if(X[p][i]==val){
            X[p].erase(X[p].begin()+i);
            break;
        }
    }
    if(X[p].empty()){
        X.erase(X.begin()+p);
        P.erase(P.begin()+p);
        S--;
    }
    else build(X[p],P[p]);
}

void add(int val){
    int p=0;
    while(p<S && val>X[p].back()) p++;
    if(p==S) p--;
    for(int i=0;i<=(int)X[p].size();i++){
        if(i==(int)X[p].size() || val<=X[p][i]){
            X[p].insert(X[p].begin()+i,val);
            break;
        }
    }
    if((int)X[p].size()==2*B){
        vector<int> nw(X[p].begin()+B,X[p].end());
        X[p].resize(B);
        X.insert(X.begin()+p+1,nw);
        P.insert(P.begin()+p+1,vector<pii>());
        build(X[p],P[p]);
        build(X[p+1],P[p+1]);
        S++;
    }
    else build(X[p],P[p]);
}

int update(int i, int y)
{
    del(V[i]);
    V[i]=y;
    add(V[i]);
    int res=1,cur=X[0][0];
    for(int i=0;i<S;i++){
        int nxt=upper_bound(X[i].begin(),X[i].end(),cur+L)-X[i].begin();
        if(nxt==(int)X[i].size()) continue;
        res+=P[i][nxt].se;
        cur=P[i][nxt].fi;
    }
    return res;
}
