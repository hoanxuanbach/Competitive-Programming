#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define maxq 500005
#define maxl 20
#define pii pair<int,int>
#define fi first
#define se second
struct query{
    int a,b,c,u,id;
    bool operator<(query o){
        if(a!=o.a) return a<o.a;
        else return u<o.u;
    }
};
bool cmp(query x,query y){
    if(x.b!=y.b) return x.b<y.b;
    else return x.id<y.id;
}
//Input
int d[3][maxn],e[maxn],q;
//Output
int res[3][maxn];
//Tree
int dt[maxn];
int n,dep[maxn],dep2[maxn],pp[maxn],f[maxn],f2[maxn],cc[maxn];
vector<int> edge[maxn],qq[maxn];
vector<pii> p[maxn];
//CDQ
query que[maxq];
int sz=0;
//BIT
namespace BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]=max(bit[i],val);
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i]);
        return res;
    }
    void del(int x){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]=0;
    }
}
//Sparse Table
namespace Sparse{
    int down[maxn][maxl];
    void build(){
        for(int i=1;i<=18;i++){
            for(int j=1;j<=n;j++) down[j][i]=down[down[j][i-1]][i-1];
        }
    }
    int query(int u,int x){
        for(int i=0;i<=18;i++){
            if(x&(1<<i)) u=down[u][i];
        }
        return u;
    }
}
//Build Tree
void dfs(int u,int par){
    pp[u]=par;dt[u]=dt[par]+1;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);
        if(dep[v]+1>dep[u]){
            f2[u]=f[u];dep2[u]=dep[u];
            f[u]=v;dep[u]=dep[v]+1;
            Sparse::down[u][0]=v;
        }
        else if(dep[v]+1>dep2[u]){dep2[u]=dep[v]+1;f2[u]=v;}
        p[u].push_back({dep[v]+1,v});
    }
}
void redfs(int u,int par,int Max,int k){
    p[u].push_back({Max,par});cc[u]=k;
    for(int v:edge[u]){
        if(v==par) continue;
        if(f[u]==v){
            if(dep2[u]>Max) redfs(v,u,dep2[u]+1,f2[u]);
            else redfs(v,u,Max+1,k);
        }
        else{
            if(dep[u]>Max) redfs(v,u,dep[u]+1,f[u]);
            else redfs(v,u,Max+1,k);
        }
    }
    while((int)p[u].size()<3) p[u].push_back({0,u});
    sort(p[u].begin(),p[u].end(),greater<pii>());
    que[++sz]={p[u][0].fi,p[u][1].fi,p[u][2].fi,u,0};
}
vector<int> ver;
void cal(int u,int par){
    ver.push_back(u);
    for(int v:edge[u]){
        if(v==par) continue;
        cal(v,u);
    }
    for(int id:qq[u]){
        vector<pii> x;
        for(int i=0;i<3;i++) x.push_back({d[i][id],i});
        sort(x.begin(),x.end(),greater<pii>());
        for(int i=0;i<3;i++){
            if(x[i].fi==0) res[x[i].se][id]=u;
            else if(p[u][i].se==par){
                int len=dt[u]-dt[pp[cc[u]]];
                if(len>=x[i].fi) res[x[i].se][id]=ver[(int)ver.size()-x[i].fi-1];
                else res[x[i].se][id]=Sparse::query(cc[u],x[i].fi-len-1);
            }
            else res[x[i].se][id]=Sparse::query(p[u][i].se,x[i].fi-1);
        }
    }
    ver.pop_back();
}
//Start CDQ
void solve(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    solve(l,mid);solve(mid+1,r);
    for(int i=l;i<=mid;i++) que[i].id=1;
    for(int i=mid+1;i<=r;i++) que[i].id=2;
    sort(que+l,que+r+1,cmp);
    for(int i=r;i>=l;i--){
        if(que[i].id==2 && que[i].u>0) BIT::update(n-que[i].c,que[i].u);
        else if(que[i].id==1 && que[i].u<0) e[-que[i].u]=max(e[-que[i].u],BIT::query(n-que[i].c));
    }
    for(int i=l;i<=r;i++){
        if(que[i].id==2 && que[i].u>0) BIT::del(n-que[i].c);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> q;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,1);redfs(1,1,0,1);
    for(int i=1;i<=q;i++){
        int dab,dbc,dca;cin >> dab >> dbc >> dca;
        if((dab+dbc+dca)%2==1) continue;
        int da=(dab+dca-dbc)/2,db=(dbc+dab-dca)/2,dc=(dbc+dca-dab)/2;
        if(da>=n || db>=n || dc>=n || da<0 || db<0 || dc<0) continue;
        d[0][i]=da;d[1][i]=db;d[2][i]=dc;
        if(da>db) swap(da,db);
        if(da>dc) swap(da,dc);
        if(db>dc) swap(db,dc);
        que[++sz]={dc,db,da,-i,0};
    }
    sort(que+1,que+sz+1);
    solve(1,sz);
    for(int i=1;i<=q;i++){
        if(e[i]==0) continue;
        qq[e[i]].push_back(i);
    }
    Sparse::build();
    cal(1,0);
    for(int i=1;i<=q;i++){
        if(e[i]==0) cout << "NIE\n";
        else{
            cout << "TAK " << res[0][i] << ' ' << res[1][i] << ' ' << res[2][i] << '\n';
        }
    }
}
