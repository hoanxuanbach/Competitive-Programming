#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int maxl = 20;
int rt[maxn],pos[maxn],deg[maxn],lst=0;
vector<int> edge[maxn];

int tree[4*maxn];
void build(int l,int r,int id){
    tree[id]=r-l+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,id<<1),build(mid+1,r,id<<1|1);
}

bool cur=true;
int update(int l,int r,int id,int tl,int tr,int p){
    if(l==r){
        tree[id]=cur;
        lst=max(lst,rt[l]);
        if(pos[l]!=-1) edge[p].push_back(pos[l]),deg[pos[l]]++;
        return l;
    }
    int mid=(l+r)>>1,val=-1;
    bool cc=cur;
    if(tr<tree[id<<1]) val=update(l,mid,id<<1,tl,tr,p);
    else if(tree[id<<1]<=tl) val=update(mid+1,r,id<<1|1,tl-tree[id<<1],tr-tree[id<<1],p);
    else{
        cur=false;
        val=update(mid+1,r,id<<1|1,0,tr-tree[id<<1],p);
        cur=cc;
        val=update(l,mid,id<<1,tl,tree[id<<1]-1,p);
    }
    cur=cc;
    tree[id]=tree[id<<1]+tree[id<<1|1];
    return val;
}

int mx[maxn][maxl],lg2[maxn];
int get(int l,int r){
    int k=lg2[r-l+1];
    return max(mx[l][k],mx[r-(1<<k)+1][k]);
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
    for(int i=0;i<N;i++) rt[i]=i,pos[i]=-1;
    build(0,N-1,1);
    for(int i=0;i<C;i++){
        lst=0;
        int fst=update(0,N-1,1,S[i],E[i],i);
        S[i]=fst,E[i]=lst;
        pos[fst]=i,rt[fst]=lst;
    }
    for(int i=0;i<N-1;i++) mx[i][0]=K[i];
    for(int i=2;i<N;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<18;i++){
        for(int j=0;j<=N-1-(1<<i);j++) mx[j][i]=max(mx[j][i-1],mx[j+(1<<(i-1))][i-1]);
    }

    int val=0,P=0;
    function<void(int,int)> dfs = [&](int u,int d){
        int Max=get(S[u],E[u]-1);
        if(Max>R) d=0;
        else d++;
        if(edge[u].empty()){
            if(d>val) val=d,P=S[u];
            else if(d==val) P=min(P,S[u]);
        }
        for(int v:edge[u]) dfs(v,d);
    };
    for(int i=0;i<C;i++) if(!deg[i]) dfs(i,0);
    return P;
}
