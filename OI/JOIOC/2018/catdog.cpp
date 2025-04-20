#include "catdog.h"
#include<bits/stdc++.h>
using namespace std;
const int inf=2e5;
const int maxn = 1e5+5;
#define pii pair<int,int>
#define fi first
#define se second

struct node{
    int x[2][2];
    node(int a=0,int b=0){
        x[0][0]=a;
        x[1][1]=b;
        x[0][1]=x[1][0]=inf;
    }
    friend node operator+(node a,node b){
        node res(inf,inf);
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) for(int p=0;p<=1;p++) for(int q=0;q<=1;q++) res.x[i][j]=min(res.x[i][j],a.x[i][p]+b.x[q][j]+(p^q));
        return res;
    }
};
struct Segtree{
    vector<node> tree;
    void build(int l,int r,int id){
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void build(int n){
        tree.assign(4*n,node());
        build(1,n,1);
    }
    void update(int l,int r,int id,int p,int va,int vb){
        if(l==r){
            tree[id].x[0][0]+=va;
            tree[id].x[1][1]+=vb;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,va,vb);
        else update(mid+1,r,id<<1|1,p,va,vb);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    pii get(){
        int a=min(tree[1].x[0][0],tree[1].x[0][1]),b=min(tree[1].x[1][0],tree[1].x[1][1]);
        return {min(a,b+1),min(b,a+1)};
    }
}ST[maxn];

int n;
vector<int> edge[maxn];

int child[maxn],son[maxn];
void pre_dfs(int u,int p){
    child[u]=1;
    for(int v:edge[u]){
        if(v==p) continue;
        pre_dfs(v,u);
        child[u]+=child[v];
        if(child[v]>child[son[u]]) son[u]=v;
    }
}

int head[maxn],par[maxn],L[maxn],cnt[maxn],pos;

void dfs(int u,int p,int t){
    if(t) head[u]=head[p];
    else head[u]=u;
    L[u]=++pos;
    par[u]=p;
    cnt[head[u]]++;
    if(son[u]) dfs(son[u],u,1);
    for(int v:edge[u]) if(v!=p && v!=son[u]) dfs(v,u,0);
}

void initialize(int N, std::vector<int> A, std::vector<int> B) {
    n=N;
    for(int i=0;i<n-1;i++){
        edge[A[i]].push_back(B[i]);
        edge[B[i]].push_back(A[i]);
    }
    pre_dfs(1,0);
    dfs(1,0,0);
    for(int i=1;i<=n;i++) if(cnt[i]) ST[i].build(cnt[i]);
}

void update(int v,int va,int vb){
    while(v){
        int u=head[v];
        pii x=ST[u].get();
        ST[u].update(1,cnt[u],1,L[v]-L[u]+1,va,vb);
        pii y=ST[u].get();
        va=y.fi-x.fi;
        vb=y.se-x.se;
        v=par[u];
    }
}

int state[maxn];

int cat(int v) {
    state[v]=1;
    update(v,inf,0);
    auto res = ST[1].get();
    return min(res.fi,res.se);
}

int dog(int v) {
    state[v]=2;
    update(v,0,inf);
    auto res = ST[1].get();
    return min(res.fi,res.se);
}

int neighbor(int v) {
    update(v,-(state[v]==1)*inf,-(state[v]==2)*inf);
    state[v]=0;
    auto res = ST[1].get();
    return min(res.fi,res.se);
}
