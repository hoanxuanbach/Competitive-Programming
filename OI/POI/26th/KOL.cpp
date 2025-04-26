#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define maxn 100005
#define maxl 20
const int bl=1300;
const int inf=1e18;
struct query{
    int u,v,id;
};
//START
int n,q,r,t[maxn],res[maxn];
vector<pii> edge[maxn];
vector<query> que[maxn];
vector<int> ver[maxn];
//BUILD PRE-TREE
int par[maxn][maxl],len[maxn],dep[maxn],L[maxn],cn[2*maxn],mn[2*maxn][maxl],sz,lg[2*maxn];
//HEAVY
int d[maxn],Min[maxn][maxl];
void pre_dfs(int u,int p,int k){
    par[u][0]=p;
    len[u]=len[p]+k;dep[u]=dep[p]+1;sz++;
    mn[sz][0]=L[u]=sz;cn[sz]=u;
    for(pii v:edge[u]){
        if(v.first==p) continue;
        pre_dfs(v.first,u,v.second);
        mn[++sz][0]=L[u];
    }
}
void build_sparse(){
    for(int i=1;i<18;i++){
        for(int j=1;j<=n;j++) par[j][i]=par[par[j][i-1]][i-1];
    }
    for(int i=1;i<=18;i++){
        for(int j=1;j<=sz-(1<<i)+1;j++) mn[j][i]=min(mn[j][i-1],mn[j+(1<<(i-1))][i-1]);
    }
}
void precal(){
    pre_dfs(1,0,0);
    build_sparse();
}
int lca(int u,int v){
    u=L[u];v=L[v];
    if(u>v) swap(u,v);
    int l=lg[v-u+1],p=min(mn[u][l],mn[v-(1<<l)+1][l]);
    return cn[p];
}
int getdist(int u,int v){
    int a=lca(u,v);
    return len[u]+len[v]-2*len[a];
}
int getMin(int u,int a){
    int f=dep[u]-dep[a],res=Min[a][0];
    for(int i=0;i<18;i++){
        if(f&(1<<i)){res=min(res,Min[u][i]);u=par[u][i];}
    }
    return res;
}
void build(int c){
    for(int i=1;i<=n;i++) d[i]=inf;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int v:ver[c]){d[v]=0;pq.push({0,v});}
    while(!pq.empty()){
        int u=pq.top().second,dt=pq.top().first;pq.pop();
        if(dt!=d[u]) continue;
        for(pii v:edge[u]){
            if(d[v.first]>dt+v.second){
                d[v.first]=dt+v.second;
                pq.push({d[v.first],v.first});
            }
        }
    }
    for(int i=1;i<=n;i++) Min[i][0]=d[i];
    for(int i=1;i<18;i++){
        for(int j=1;j<=n;j++) Min[j][i]=min(Min[j][i-1],Min[par[j][i-1]][i-1]);
    }
}
void solve_heavy(int i){
    build(i);
    for(auto c:que[i]){
        int anc=lca(c.u,c.v);
        res[c.id]=min(res[c.id],getdist(c.u,c.v)+2*min(getMin(c.u,anc),getMin(c.v,anc)));
    }
}
void solve_light(int i){
    if((int)ver[i].size()==0) return;
    for(auto c:que[i]){
        for(int v:ver[i]) res[c.id]=min(res[c.id],getdist(c.u,v)+getdist(c.v,v));
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> r;
    for(int i=2;i<=2*n;i++) lg[i]=lg[i/2]+1;
    for(int i=1;i<=n;i++){cin >> t[i];ver[t[i]].push_back(i);}
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    precal();
    cin >> q;
    for(int i=1;i<=q;i++){
        int u,v,w;cin >> u >> v >> w;
        que[w].push_back({u,v,i});
        res[i]=inf;
    }
    for(int i=1;i<=r;i++){
        if((int)ver[i].size()<=bl) solve_light(i);
        else solve_heavy(i);
    }
    for(int i=1;i<=q;i++){
        if(res[i]==inf) cout << -1 << '\n';
        else cout << res[i] << '\n';
    }
}
