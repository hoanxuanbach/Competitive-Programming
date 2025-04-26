#include <bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
const int maxn = 1e5+5;
const int maxl = 20;
const int inf = 1e18;
#define pii pair<int,int>
#define fi first
#define se second

int n,A[maxn],B[maxn];
vector<pii> edge[maxn];

//CHT
struct line{
    int a,b,p;
    bool operator<(line l){return a>l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    bool empty(){
        return x.empty();
    }
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a) l.p=(l.b<y.b)?inf:-inf;
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    int query(int v){
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l.a*v+l.b;
    }
}cht[maxn];

//Tree
int Min[2*maxn][maxl];
int lg2[2*maxn],dep[maxn],L[maxn],R[maxn],T;

int cmp(int u,int v){
    return (L[u]<L[v]?u:v);
}
int lca(int u,int v){
    u=L[u];v=L[v];
    if(u>v) swap(u,v);
    int p=lg2[v-u+1];
    return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
}
int dist(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
}
void dfs(int u,int p){
    L[u]=++T;Min[T][0]=u;
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        dep[v]=dep[u]+w;
        dfs(v,u);Min[++T][0]=u;
    }
    R[u]=T;
}
void build(){
    dfs(1,0);
    for(int i=2;i<=T;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<20;i++){
        for(int j=1;j<=(T-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
}

//Centroid
int child[maxn],sz,dad[maxn];
bool used[maxn];

void dfs_sz(int u,int p){
    child[u]=1;
    for(auto [v,w]:edge[u]){
        if(v==p || used[v]) continue;
        dfs_sz(v,u);child[u]+=child[v];
    }
}
int findcen(int u,int p){
    for(auto [v,w]:edge[u]){
        if(v==p || used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}

int decompose(int u){
    dfs_sz(u,0);sz=child[u];
    u=findcen(u,0);used[u]=true;
    for(auto [v,w]:edge[u]) if(!used[v]) dad[decompose(v)]=u;
    return u;
}

void update(int u,int val){
    int x=u;
    while(x){
        cht[x].add({B[u],val+B[u]*dist(u,x),inf});
        x=dad[x];
    }
}
int query(int u){
    int x=u,res=inf;
    while(x){
        if(!cht[x].empty()) res=min(res,cht[x].query(dist(u,x)));
        x=dad[x];
    }
    return res;
}

std::vector<int> travel(std::vector<int> _A,
        std::vector<i32> _B, std::vector<i32> _U, std::vector<i32> _V, std::vector<i32> _W)
{
    n=(int)_A.size();
    for(int i=0;i<n;i++) A[i+1]=_A[i],B[i+1]=_B[i];
    for(int i=0;i<n-1;i++){
        int u=_U[i]+1,v=_V[i]+1,w=_W[i];
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    build();
    decompose(1);
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return B[x]>B[y];
    });
    for(int u:ord){
        int val=(u!=1?query(u):0);
        if(val==inf) continue;
        update(u,val+A[u]);
    }
    vector<int> res(n-1);
    for(int i=2;i<=n;i++) res[i-2]=query(i);
    return res;
}

#undef int