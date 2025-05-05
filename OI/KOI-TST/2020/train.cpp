#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = 1e18;
const int maxn = 250005;
const int L = 20;

vector<int> edge[maxn];
int dep[maxn],par[maxn][25];

array<int,2> val[maxn];
void add(int u,int x){
    if(val[u][0]<x) swap(val[u][0],x);
    if(val[u][1]<x) swap(val[u][1],x);
}

void dfs(int u,int p){
    par[u][0]=p,dep[u]=dep[p]+1;
    for(int i=1;i<L;i++) par[u][i]=par[par[u][i-1]][i-1];
    for(int v:edge[u]) if(v!=p){
        dfs(v,u);
        add(u,val[v][0]+1);
    }
}

void redfs(int u,int p){
    int dist=(val[p][0]==val[u][0]+1?val[p][1]:val[p][0]);
    add(u,dist+1);

    //cout << u << ' ' << val[u][0] << ' ' << val[u][1] << '\n';
    for(int v:edge[u]) if(v!=p) redfs(v,u);
}

void init(int N, vector<int> X, vector<int> Y) {
    for(int i=0;i<N-1;i++) edge[X[i]].push_back(Y[i]),edge[Y[i]].push_back(X[i]);
    val[0]={-1,-1};
    dfs(1,0),redfs(1,0);
}

int lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    for(int i=0;i<L;i++) if((dep[v]-dep[u])>>i&1) v=par[v][i];
    if(u==v) return u;
    for(int i=L-1;i>=0;i--) if(par[v][i]!=par[u][i]) u=par[u][i],v=par[v][i];
    return par[u][0];
}

vector<int> get_path(int u,int v){
    int x=lca(u,v);

    vector<int> path;
    while(u!=x) path.push_back(u),u=par[u][0];

    vector<int> nxt;
    while(v!=x) nxt.push_back(v),v=par[v][0];
    reverse(nxt.begin(),nxt.end());

    path.push_back(x);
    path.insert(path.end(),nxt.begin(),nxt.end());
    return path;
}

int get_root(int a,int b,int c){
    return lca(a,b)^lca(a,c)^lca(b,c);
}
int get_dist(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
}

int max_dist(int u,int v){
    return (val[u][0]==val[v][0]+1?val[u][1]:val[u][0]);
}

ll move(int a,int b,int x){
    
    vector<int> p=get_path(a,b);
    int id=get_dist(a,x);

    int l=id,r=id,len=(int)p.size()-1;

    ll res=0;
    int mn=id,mx=id-1;

    for(int i=0;;i^=1){
        if(r-l>=len) break;
        if(i){
            while(r<len && max_dist(p[r+1],p[r])+r-l+1>=len){
                //cout << "* " << p[r+1] << ' ' << p[r] << ' ' << max_dist(p[r+1],p[r]) << '\n';
                r++;
            }
            res+=len-(r-l);
        }
        else{
            while(0<l && max_dist(p[l-1],p[l])+r-l+1>=len) l--;
            res+=len-(r-l);
        }
        if(mn<=l && r<=mx) return inf;
        mn=min(mn,l),mx=max(mx,r);
    }
    //cout << a << ' ' << b << ' ' << x << ' ' << res << '\n';
    return res;
}

ll get(int a,int b,int x){
    return min(move(a,b,x),move(b,a,x));
}

ll train(std::vector<int> Z) {
    int a=Z[0],b=Z[1],c=Z[2],d=Z[3];
    int dist=get_dist(a,b);
    int x=get_root(a,b,c),y=get_root(c,d,a);
    ll res=get(a,b,x)+get(c,d,y)+dist+get_dist(x,y);
    return (res>=inf?-1:res);
}