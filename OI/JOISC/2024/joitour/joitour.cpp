#include "joitour.h"
#include<bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
const int maxn = 2e5+5;
int N,C[maxn];
vector<int> edge[maxn];

int L[maxn],R[maxn],T,ans,P[maxn];
int child[maxn],son[maxn],head[maxn],lst[maxn],par[maxn];

void pre_dfs(int u,int p){
    child[u]=1;par[u]=p;
    for(int v:edge[u]){
        if(v==p) continue;
        pre_dfs(v,u);
        child[u]+=child[v];
        if(child[v]>child[son[u]]) son[u]=v;
    }
}
void hld_dfs(int u,int p,int t){
    L[u]=++T;P[T]=u;
    if(t) head[u]=head[p];
    else head[u]=u;
    //cout << "head " << u << ' ' << head[u] << ' ' << head[p] << '\n';
    lst[head[u]]=u;
    if(son[u]) hld_dfs(son[u],u,1);
    for(int v:edge[u]) if(v!=p && v!=son[u]) hld_dfs(v,u,0);
    R[u]=T;
}

struct Node{
    int s0=0,s2=0,c0=0,c2=0;
    int sum=0,total=0;
    Node(int s0=0,int s2=0,int c0=0,int c2=0):s0(s0),s2(s2),c0(c0),c2(c2){
        sum=c0*c2;
    }
    friend Node operator+(Node a,Node b){
        Node res;
        res.s0=a.s0+b.s0;
        res.s2=a.s2+b.s2;
        res.c0=a.c0+b.c0;
        res.c2=a.c2+b.c2;
        res.sum=a.sum+b.sum;
        res.total=a.total+b.total+a.c0*b.s2+a.c2*b.s0+a.s0*b.c2+a.s2*b.c0;
        return res;
    };
    friend Node operator-(Node a,Node b){
        Node res;
        res.s0=a.s0-b.s0;
        res.s2=a.s2-b.s2;
        res.c0=a.c0-b.c0;
        res.c2=a.c2-b.c2;
        res.sum=a.sum-b.sum;
        res.total=a.total-b.total-(res.c0*b.s2+res.c2*b.s0+res.s0*b.c2+res.s2*b.c0);
        return res;
    };
}cc[maxn];
struct node{
    int total=0;
    int c0=0,c1=0,c2=0;
    int l0=0,l2=0,r0=0,r2=0;
    node(){}
    friend node operator+(node a,node b){
        node res;
        res.c0=a.c0+b.c0;
        res.c1=a.c1+b.c1;
        res.c2=a.c2+b.c2;
        res.l0=a.l0+b.l0+a.c0*b.c1;
        res.l2=a.l2+b.l2+a.c2*b.c1;
        res.r0=a.r0+b.r0+a.c1*b.c0;
        res.r2=a.r2+b.r2+a.c1*b.c2;
        res.total=a.total+b.total+a.l0*b.c2+a.l2*b.c0+a.c0*b.r2+a.c2*b.r0;
        return res;
    }
}tree[4*maxn];
node query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return node();
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}
void update(int l,int r,int id,int p,node val){
    if(l==r){
        tree[id]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p,val);
    else update(mid+1,r,id<<1|1,p,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void change(i32 u, i32 d) {
    //cout << "change " << u << ' ' << d << '\n';
    u++;C[u]=d;
    while(u){
        int v=head[u],w=lst[v],p=par[v];
        //cout << u << ' ' << v << ' ' << w << '\n';
        node cur=query(1,N,1,L[v],L[w]);
        ans-=cur.total;
        if(p) cc[p]=cc[p]-Node(cur.r0,cur.r2,cur.c0,cur.c2);
        node val;
        val.total=cc[u].total;
        val.l0=val.r0=cc[u].s0;
        val.l2=val.r2=cc[u].s2;
        val.c0=cc[u].c0;
        val.c2=cc[u].c2;
        node add;
        if(C[u]==0) add.c0++;
        else if(C[u]==2) add.c2++;
        else{
            add.c1++;
            add.total+=cc[u].c0*cc[u].c2-cc[u].sum;
        }
        val=val+add;
        //cout << val.c0 << ' ' << val.c1 << ' ' << val.c2 << ' ' << val.l0 <<  ' ' << val.l2 << ' ' << val.r0 << ' ' << val.r2 << ' ' << val.total << '\n';
        val.l0=val.r0=max(val.l0,val.r0);
        val.l2=val.r2=max(val.l2,val.r2);
        update(1,N,1,L[u],val);
        cur=query(1,N,1,L[v],L[w]);
        ans+=cur.total;
        if(p) cc[p]=cc[p]+Node(cur.r0,cur.r2,cur.c0,cur.c2);
        u=p;
    }
}

void init(i32 _N, std::vector<i32> F, std::vector<i32> U, std::vector<i32> V,
          i32 Q) {
    N=_N;
    for(int i=0;i<N-1;i++){
        U[i]++;V[i]++;
        edge[U[i]].push_back(V[i]);
        edge[V[i]].push_back(U[i]);
    }
    pre_dfs(1,0);
    hld_dfs(1,0,0);
    for(int i=1;i<=N;i++){
        int u=P[i];
        change(u-1,F[u-1]);
    }
}



long long num_tours() {
    return ans;
}

#undef int
