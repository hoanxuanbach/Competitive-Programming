#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int maxn = 250005;
#define pii pair<int,int>
#define fi first
#define se second
int f(int x){
    return (1LL*x*(x+1)/2)%mod;
}

struct node{
    int lt=0,ls=1,rt=0,rs=1,total=0,sz=1;
    node(){}
    friend node operator+(node a,node b){
        node res;
        res.sz=a.sz+b.sz;
        res.lt=a.lt;res.rt=b.rt;
        res.ls=(a.ls+(a.ls==a.sz && b.lt==a.lt)*b.ls);
        res.rs=(b.rs+(b.rs==b.sz && a.rt==b.rt)*a.rs);
        res.total=(a.total+b.total)%mod;
        if(a.rt==b.lt){
            if(a.rs!=a.sz && b.ls!=b.sz) res.total=(res.total+f(a.rs+b.ls))%mod;
        }
        else{
            if(a.rs!=a.sz) res.total=(res.total+f(a.rs))%mod;
            if(b.ls!=b.sz) res.total=(res.total+f(b.ls))%mod;
        }
        return res;
    }
};

node tree[4*maxn];
void update(int l,int r,int id,int p){
    if(l==r){
        tree[id].lt^=1;
        tree[id].rt^=1;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void build(int l,int r,int id){
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

vector<pii> edge[maxn];
int child[maxn],son[maxn];
void pre_dfs(int u,int p){
    child[u]=1;
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        pre_dfs(v,u);child[u]+=child[v];
        if(child[v]>child[son[u]]) son[u]=v;
    }
}

int N,res;

void add(int u,int p){
    update(1,N,1,u);
    for(auto [v,w]:edge[u]) if(v!=p) add(v,u);
}

void dfs(int u,int p,int val,int t){
    int W=-1;
    for(auto [v,w]:edge[u]){
        if(v!=p && v!=son[u]) dfs(v,u,w,1);
        else if(v==son[u]) W=w;
    }
    if(son[u]) dfs(son[u],u,W,0);
    update(1,N,1,u);
    for(auto [v,w]:edge[u]) if(v!=p && v!=son[u]) add(v,u);
    int sum=tree[1].total;
    if(tree[1].ls!=tree[1].sz){
        sum=(sum+f(tree[1].ls))%mod;
        sum=(sum+f(tree[1].rs))%mod;
    }
    else sum=(sum+f(tree[1].sz))%mod;
    sum=(f(N)-sum+mod)%mod;
    res=(res+1LL*val*sum%mod)%mod;
    if(t) add(u,p);
}

int maintenance_costs_sum(std::vector<int> U, std::vector<int> V, std::vector<int> W) {
	N = U.size() + 1;
    for(int i=0;i<N-1;i++){
        U[i]++;V[i]++;
        edge[U[i]].push_back({V[i],W[i]});
        edge[V[i]].push_back({U[i],W[i]});
    }
    pre_dfs(1,0);
    build(1,N,1);
    dfs(1,0,0,0);
    return res;
}
