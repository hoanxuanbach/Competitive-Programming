#include "icc.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
#define pii pair<int,int>
#define fi first
#define se second
int s[2][maxn],sz[2],par[maxn],n;
vector<int> ver[maxn],ss[maxn],cur[2];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    par[v]=u;
    for(int x:ver[v]) ver[u].push_back(x);
    ver[v].clear();
}
void add(int t,int x){
    for(int v:ver[x]) s[t][sz[t]++]=v;
}
pii cal(){
    for(int i=0;i<n;i++) ss[i].clear();
    int len=1;
    for(int i=1;i<=n;i++){
        if(ver[i].empty()) continue;
        ss[0].push_back(i);
    }
    while(true){
        sz[0]=sz[1]=0;
        for(int i=0;i<len;i++){
            int ssz=(int)ss[i].size();
            for(int j=0;j<(ssz+1)/2;j++) add(0,ss[i][j]);
            for(int j=(ssz+1)/2;j<ssz;j++) add(1,ss[i][j]);
        }
        if(query(sz[0],sz[1],s[0],s[1])) break;
        int prelen=len;
        for(int i=0;i<prelen;i++){
            int ssz=(int)ss[i].size();
            if(ssz==1) continue;
            for(int j=(ssz+1)/2;j<ssz;j++){
                ss[len].push_back(ss[i].back());
                ss[i].pop_back();
            }
            len++;
        }
    }
    cur[0].clear();cur[1].clear();
    for(int i=0;i<sz[0];i++) cur[0].push_back(s[0][i]);
    for(int i=0;i<sz[1];i++) cur[1].push_back(s[1][i]);
    int l=0,r=sz[0]-1,f0=cur[0][0],f1=cur[1][0];
    while(l<r){
        int mid=(l+r)>>1;sz[0]=0;
        for(int i=l;i<=mid;i++) s[0][sz[0]++]=cur[0][i];
        if(query(sz[0],sz[1],s[0],s[1])) r=mid;
        else l=mid+1;
        f0=cur[0][l];
    }
    sz[0]=1;s[0][0]=f0;
    l=0;r=sz[1]-1;
    while(l<r){
        int mid=(l+r)>>1;sz[1]=0;
        for(int i=l;i<=mid;i++) s[1][sz[1]++]=cur[1][i];
        if(query(sz[0],sz[1],s[0],s[1])) r=mid;
        else l=mid+1;
        f1=cur[1][l];
    }
    return {f0,f1};
}
void run(int N){
    n=N;
    for(int i=1;i<=n;i++){ver[i].push_back(i);par[i]=i;}
    for(int i=1;i<n;i++){
        pii x=cal();
        setRoad(x.fi,x.se);
        unions(x.fi,x.se);
    }
}
