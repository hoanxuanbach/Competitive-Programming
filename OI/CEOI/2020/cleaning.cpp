#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;

int n,q,leaf[maxn];
vector<int> edge[maxn];

int child[maxn],son[maxn],dd[maxn];
void dfs(int u,int p){
    dd[u]=leaf[u],child[u]=1;
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);dd[u]^=dd[v];
        child[u]+=child[v];
        if(child[v]>child[son[u]]) son[u]=v;
    }
}
int L[maxn],R[maxn],head[maxn],par[maxn],ord[maxn],T;
void hld_dfs(int u,int p,int t){
    par[u]=p;
    if(t) head[u]=head[p];
    else head[u]=u;
    L[u]=++T;ord[T]=u;
    if(son[u]) hld_dfs(son[u],u,1);
    for(int v:edge[u]) if(v!=p && v!=son[u]) hld_dfs(v,u,0);
    R[u]=T;
}

int tree[4*maxn],lazy[4*maxn];
void build(int l,int r,int id){
    if(l==r){
        tree[id]=(dd[ord[l]]^1);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void getnew(int l,int r,int id){
    lazy[id]^=1;
    tree[id]=(r-l+1)-tree[id];
}
void pushdown(int l,int r,int id){
    if(!lazy[id]) return;
    int mid=(l+r)>>1;
    getnew(l,mid,id<<1);
    getnew(mid+1,r,id<<1|1);
    lazy[id]=0;
}
void update(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(l,r,id);
        return;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int cnt=0;
    for(int i=1;i<=n;i++) cnt^=(leaf[i]=((int)edge[i].size()==1));
    dfs(1,0);
    hld_dfs(1,0,0);
    build(1,n,1);
    for(int i=1;i<=q;i++){
        int sz;cin >> sz;
        int cur=cnt^(sz&1);
        vector<int> add,lf;
        for(int j=1;j<=sz;j++){
            int u;cin >> u;
            if(leaf[u]) cur^=1,leaf[u]=false,lf.push_back(u);
            else{
                add.push_back(u);
                while(u){
                    update(1,n,1,L[head[u]],L[u]);
                    u=par[head[u]];
                }
            }
        }
        if(!cur) cout << n-2+sz+tree[1] << '\n';
        else cout << -1 << '\n';
        for(int u:lf) leaf[u]=true;
        for(int u:add){
            while(u){
                update(1,n,1,L[head[u]],L[u]);
                u=par[head[u]];
            }
        }
    }
}
