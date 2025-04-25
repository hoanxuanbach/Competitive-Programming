#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
const int maxl = 25;
int n,m,q;
struct Tree{
    int L[maxn],T,rt=-1;
    vector<int> edge[maxn];
    int dep[maxn],par[maxn][maxl];
    void dfs(int u,int p){
        L[u]=++T;
        par[u][0]=p,dep[u]=dep[p]+1;
        for(int i=1;i<20;i++) par[u][i]=par[par[u][i-1]][i-1];
        for(int v:edge[u]) dfs(v,u);
    }
    int lca(int u,int v){
        if(dep[u]>dep[v]) swap(u,v);
        for(int i=0;i<20;i++) if((dep[v]-dep[u])>>i&1) v=par[v][i];
        if(u==v) return u;
        for(int i=19;i>=0;i--) if(par[u][i]!=par[v][i]) u=par[u][i],v=par[v][i];
        return par[u][0];
    }

    int f[maxn],d[maxn];
    int findpar(int u){
        if(u==f[u]) return u;
        int x=f[u];f[u]=findpar(f[u]);
        d[u]+=d[x];
        return f[u];
    }
    void unions(int u,int v,int w){
        int pu=findpar(u),pv=findpar(v);
        if(pu==pv) return;
        f[pv]=pu;d[pv]+=d[u]-d[v]+w;
    }

    void build(){
        iota(f+1,f+n+1,1);
        for(int i=1;i<=n;i++){
            int p;cin >> p;
            if(p==-1) rt=i;
            else edge[p].push_back(i);
        }
        dfs(rt,0);
    }
}T1,T2;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q >> q;
    T1.build();T2.build();
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return T1.L[x]<T1.L[y];
    });
    while((int)ord.size()>m) ord.pop_back();
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return T2.L[x]<T2.L[y];
    });
    for(int i=0;i<m;i++) cout << ord[i] << ' ';
    cout << endl;
    for(int i=1;i<m;i++) cout << "? " << ord[i-1] << ' ' << ord[i] << '\n';
    cout << "!" << endl;
    for(int i=1;i<m;i++){
        int u=ord[i-1],v=ord[i];
        int x,y,a=T1.lca(u,v);cin >> x >> y;
        T1.unions(a,u,x);T1.unions(a,v,y);
        a=T2.lca(u,v);cin >> x >> y;
        T2.unions(a,u,x);T2.unions(a,v,y);
    }
    for(int i=1;i<=n;i++) T1.findpar(i),T2.findpar(i);
    vector<int> U(q),V(q);
    for(int i=0;i<q;i++) cin >> U[i] >> V[i];
    for(int i=0;i<q;i++){
        int u=U[i],v=V[i];
        int a=T1.lca(u,v);
        cout << T1.d[u]+T1.d[v]-2*T1.d[a] << ' ';
        a=T2.lca(u,v);
        cout << T2.d[u]+T2.d[v]-2*T2.d[a] << '\n';
    }
    cout << endl;
}