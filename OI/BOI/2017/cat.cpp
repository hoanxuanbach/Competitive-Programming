#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define maxn 400005
#define maxl 25
const int inf=1e9;
int n,d,depth[maxn],Min[maxn][maxl],L[maxn],len,logx[maxn];
int dad[maxn],res[maxn],child[maxn],sz;
bool used[maxn];
vector<int> edge[maxn];
void dfs(int u,int par){
    L[u]=++len;Min[len][0]=len;
    depth[L[u]]=depth[L[par]]+1;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);
        Min[++len][0]=L[u];
    }
}
void build_sparse(){
    for(int i=1;i<=18;i++){
        for(int j=1;j<=(len-(1<<i)+1);j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
    for(int i=2;i<=len;i++) logx[i]=logx[i/2]+1;
}
void dfs2(int u,int par){
    child[u]=1;
    for(int v:edge[u]){
        if(v==par || used[v]) continue;
        dfs2(v,u);child[u]+=child[v];
    }
}
int findcen(int u,int par){
    for(int v:edge[u]){
        if(v==par || used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}
void decompose(int u,int par){
    dfs2(u,par);sz=child[u];
    int cen=findcen(u,par);
    dad[cen]=par;used[cen]=true;
    for(int v:edge[cen]){
        if(v==par || used[v]) continue;
        decompose(v,cen);
    }
}
int dist(int u,int v){
    u=L[u];v=L[v];
    if(u>v) swap(u,v);
    int p=logx[v-u+1],a=min(Min[u][p],Min[v-(1<<p)+1][p]);
    return depth[u]+depth[v]-2*depth[a];
}
void update(int u){
    int a=u;
    while(a!=0){
        res[a]=min(res[a],dist(a,u));
        a=dad[a];
    }
}
int query(int u){
    int r=inf,a=u;
    while(a!=0){
        r=min(r,dist(u,a)+res[a]);
        a=dad[a];
    }
    return r;
}
signed  main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> d;
    for(int i=2;i<=n;i++){
        int p;cin >> p;
        edge[p+1].push_back(i);
        edge[i].push_back(p+1);
    }
    dfs(1,0);build_sparse();
    decompose(1,0);
    vector<pii> p;
    for(int i=1;i<=n;i++){
        res[i]=inf;
        p.push_back({depth[L[i]],i});
    }
    sort(p.begin(),p.end(),greater<pii>());
    int ans=0;
    for(auto it:p){
        if(query(it.second)>=d){ans++;update(it.second);}
    }
    cout << ans << '\n';
}
