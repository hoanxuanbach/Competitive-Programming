#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define int long long 
#define pii pair<int,int>
const int mod = 998244353;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
const int maxn = 150005;
const int inf = 1e18;

struct DS{
    ordered_set<pii> T;
    void add(pii x){
        T.insert(x);
    }
    void del(pii x){
        T.erase(x);
    }
    int get(int k){
        if(k<=0) return 0LL;
        if(k>(int)T.size()) return inf;
        return T.find_by_order(k-1)->first;
    }
}S[maxn];

int N,Q;
int C[maxn],DD[maxn],D[maxn],F[maxn];
vector<pii> g[maxn];

int L[maxn],R[maxn],cn[maxn],TT;
int head[maxn],par[maxn],son[maxn],sz[maxn],leaf[maxn];

int dp[maxn],A[maxn],B[maxn];

struct SegTree{
    struct node{
        int la=inf,lb=0,lc=0;
        int ra=inf,rb=0,rc=0;
        friend node operator+(node x,node y){
            node z;
            z.la=min(y.la-x.lc,max(x.la,y.lb-x.lc));
            z.lb=max(y.lb-x.lc,x.lb);
            z.lc=x.lc+y.lc;

            z.rb=max(x.rb-y.rc,y.rb);
            z.ra=min(x.ra-y.rc,max(y.ra,x.rb-y.rc));
            z.rc=x.rc+y.rc;
            return z;
        }
    }T[4*maxn];
    /*
    x-> min(A,max(B,x))+C
    */
    void build(int l,int r,int id){
        if(l==r){
            int x=cn[l];
            T[id].la=T[id].ra=A[x];
            T[id].lb=T[id].rb=B[x];
            T[id].lc=D[son[x]];
            T[id].rc=D[x];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        T[id]=T[id<<1]+T[id<<1|1];
    }
    void update(int l,int r,int id,int k){
        if(l==r){
            int x=cn[l];
            T[id].la=T[id].ra=A[x];
            T[id].lb=T[id].rb=B[x];
            T[id].lc=D[son[x]];
            T[id].rc=D[x];
            return;
        }
        int mid=(l+r)>>1;
        if(k<=mid) update(l,mid,id<<1,k);
        else update(mid+1,r,id<<1|1,k);
        T[id]=T[id<<1]+T[id<<1|1];
    }
    int query_left(int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return x;
        if(tl<=l && r<=tr) return min(T[id].la,max(T[id].lb,x))+T[id].lc;
        int mid=(l+r)>>1;
        return query_left(mid+1,r,id<<1|1,tl,tr,query_left(l,mid,id<<1,tl,tr,x));
    }
    int query_right(int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return x;
        if(tl<=l && r<=tr) return min(T[id].ra,max(T[id].rb,x))+T[id].rc;
        int mid=(l+r)>>1;
        return query_right(l,mid,id<<1,tl,tr,query_right(mid+1,r,id<<1|1,tl,tr,x));
    }
}ST;

void pre_dfs(int u,int p){
    sz[u]=1;
    par[u]=p;
    for(auto [v,id]:g[u]){
        if(v==p) continue;
        F[id]=v;
        pre_dfs(v,u);sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}
void hld_dfs(int u,int p,int t){
    L[u]=++TT;cn[TT]=u;
    if(t) head[u]=head[p];
    else head[u]=u;

    int x=son[u];
    if(x){
        hld_dfs(x,u,1);
        S[u].add({dp[x]+D[x],x});
        leaf[u]=leaf[x];
    }
    else leaf[u]=u;
    for(auto [v,id]:g[u]){
        if(v==p || v==son[u]) continue;
        hld_dfs(v,u,0);
        S[u].add({dp[v]+D[v],v});
    }
    R[u]=TT;
    dp[u]=S[u].get(C[u]);
    if(x) S[u].del({dp[x]+D[x],x});
    A[u]=S[u].get(C[u]);
    B[u]=S[u].get(C[u]-1);

    //cout << "dp " << u << ' ' << dp[u] << '\n';
}

void solve(){
    cin >> N;
    for(int i=1;i<N;i++){
        int u,v;cin >> u >> v >> DD[i];
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }
    for(int i=1;i<=N;i++) cin >> C[i];
    pre_dfs(1,0);
    for(int i=1;i<N;i++) D[F[i]]=DD[i];
    hld_dfs(1,0,0);
    ST.build(1,N,1);

    auto query = [&](int u){
        int x=leaf[u];
        return ST.query_right(1,N,1,L[u],L[x],inf)-D[u];
    };

    auto update = [&](int v){
        A[v]=S[v].get(C[v]);
        B[v]=S[v].get(C[v]-1);
        ST.update(1,N,1,L[v]);

        while(v){
            int u=head[v],x=par[u];
            if(!x) break;
            int val=query(u);
            S[x].del({dp[u]+D[u],u});
            //cout << "update dp " << u << ' ' << val << '\n';
            dp[u]=val;
            S[x].add({dp[u]+D[u],u});
            A[x]=S[x].get(C[x]);
            B[x]=S[x].get(C[x]-1);
            ST.update(1,N,1,L[x]);
            v=x;
        }
    };

    function<int(int)> get = [&](int v){
        if(v==1) return inf;
        if(head[v]==1) return ST.query_left(1,N,1,1,L[v]-1,inf);
        int u=head[v];
        int x=par[u],val=get(x),k=son[x],dk=query(k)+D[k];
        S[x].add({dk,k});
        S[x].del({dp[u]+D[u],u});
        S[x].add({val,par[x]});
        int ret=S[x].get(C[x])+D[u];
        S[x].del({val,par[x]});
        S[x].add({dp[u]+D[u],u});
        S[x].del({dk,k});
        if(v==u) return ret;
        else return ST.query_left(1,N,1,L[u],L[v]-1,ret);
    };

    cin >> Q;
    for(int i=0;i<Q;i++){
        int op;cin >> op;
        if(op==1){
            int v;cin >> v >> C[v];
            update(v);
        }
        else if(op==2){
            int v;cin >> v;v=F[v];
            int u=par[v];
            if(son[u]==v) cin >> D[v];
            else{
                S[u].del({dp[v]+D[v],v});
                cin >> D[v];
                S[u].add({dp[v]+D[v],v});    
            }
            ST.update(1,N,1,L[v]);
            update(u);
        }
        else{
            int v;cin >> v;
            vector<pii> add;
            if(son[v]) add.push_back({query(son[v])+D[son[v]],son[v]});
            if(par[v]) add.push_back({get(v),par[v]});
            for(auto x:add) S[v].add(x);
            int res=S[v].get(C[v]);
            cout << (res>=inf?-1:res) << '\n';
            for(auto x:add) S[v].del(x);
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
