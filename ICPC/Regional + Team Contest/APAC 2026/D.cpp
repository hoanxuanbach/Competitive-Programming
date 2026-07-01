#include <bits/stdc++.h>

using namespace std;

#define int long long 
const int N = 2e5 + 5;
const int inf = 1e18;

int p[N],head[N],sz[N],son[N],cn[N],leaf[N];
int L[N],R[N],T;
vector<int> g[N];

int a[N],s[N],f[N];

void pre_dfs(int u){
    sz[u]=1;
    for(int v:g[u]){
        pre_dfs(v);f[u]+=f[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
        sz[u]+=sz[v];
    }
    f[u]=max(f[u],a[u]);
}
int hld_dfs(int u,int t){
    L[u]=++T;cn[T]=u;
    if(!t) head[u]=u;
    else head[u]=head[p[u]];
    if(son[u]) leaf[u]=hld_dfs(son[u],1);
    else leaf[u]=u;
    for(int v:g[u]) if(v!=son[u]) hld_dfs(v,0),s[u]+=f[v];
    R[u]=T;
    //cout << u << ' ' << s[u] << ' ' << a[u] << ' ' << f[u] << '\n';
    return leaf[u];
}

struct node{
    int a=-inf,b=0;
    node(){}
    friend node operator +(node x,node y){
        node z;
        z.a=max(y.a,x.a-y.b);
        z.b=x.b+y.b;
        return z;
    }
};

node Tree[4*N];
void build(int l,int r,int id){
    if(l==r){
        int u=cn[l];
        Tree[id].a=a[u]-s[u];
        Tree[id].b=s[u];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    Tree[id]=Tree[id<<1]+Tree[id<<1|1];
}
void update(int l,int r,int id,int x,int A,int B){
    if(l==r){
        Tree[id].a=A;
        Tree[id].b=B;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x,A,B);
    else update(mid+1,r,id<<1|1,x,A,B);
    Tree[id]=Tree[id<<1]+Tree[id<<1|1];
}
node query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return node();
    if(tl<=l && r<=tr) return Tree[id];
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}

void solve() {
    int n,q;cin >> n >> q;

    T=0;
    for(int i=0;i<=n;i++){
        g[i].clear();
        s[i]=a[i]=f[i]=0;
        head[i]=p[i]=son[i]=sz[i]=son[i]=L[i]=R[i]=cn[i]=leaf[i]=0;
    }
    for(int i=2;i<=n;i++){
        cin >> p[i];
        g[p[i]].push_back(i);
    }

    for(int i=1;i<=n;i++) cin >> a[i];
    pre_dfs(1);
    hld_dfs(1,0);
    build(1,n,1);

    auto get = [&](int u){
        int l=L[u],r=L[leaf[u]];
        node cur=query(1,n,1,l,r);
        //cout << u << ' ' << l << ' ' << r << ' ' << cur.a << ' ' << cur.b << '\n';
        return max(cur.a,0LL)+cur.b;
    };

    auto fix = [&](int u,int val){
        a[u]=val;
        update(1,n,1,L[u],a[u]-s[u],s[u]);
        while(head[u]>1){
            int v=head[u];
            int nf=get(v);
            int x=p[v];
            s[x]=s[x]-f[v]+nf;f[v]=nf;
            update(1,n,1,L[x],a[x]-s[x],s[x]);
            u=x;
        }
    };  

    cout << get(1) << '\n';
    for(int i=0;i<q;i++){
        int u,x;cin >> u >> x;
        fix(u,x);
        cout << get(1) << '\n';
    }

}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_test = 1;
    cin >> num_test;
    while (num_test--) {
        solve();
    }
}