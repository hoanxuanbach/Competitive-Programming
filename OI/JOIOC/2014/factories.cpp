#include "factories.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
#define piii pair<ll,pii>
#define se second
#define fi first
#define maxn 500005
#define maxl 22
const ll inf=1e18;
vector<pii> edge[maxn],adj[maxn];
ll n,q,sz,cnt,len,L[maxn],R[maxn],Min[2*maxn][maxl],cn[2*maxn],f[maxn],lg[2*maxn],dep[maxn];
int scc[maxn];
bool cmp(int a,int b){
    return L[a]<L[b];
}
void dfs(ll u,ll par){
    L[u]=++cnt;len++;
    f[u]=Min[len][0]=len;cn[len]=u;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        dep[v.first]=dep[u]+v.second;
        dfs(v.first,u);
        Min[++len][0]=f[u];
    }
    R[u]=cnt;
}
ll lca(ll u,ll v){
    u=f[u];v=f[v];
    if(u>v) swap(u,v);
    ll p=lg[v-u+1],a=min(Min[u][p],Min[v-(1<<p)+1][p]);
    return cn[a];
}
ll getdist(ll u,ll v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
}
void build_sparse(){
    for(ll i=2;i<=len;i++) lg[i]=lg[i/2]+1;
    for(ll i=1;i<20;i++){
        for(ll j=1;j<=(len-(1<<i)+1);j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
}
ll Min1[maxn],Min2[maxn];
void dfs2(int u){
    Min1[u]=Min2[u]=inf;
    for(pii v:adj[u]){
        dfs2(v.first);
        Min1[u]=min(Min1[u],Min1[v.first]+v.second);
        Min2[u]=min(Min2[u],Min2[v.first]+v.second);
    }
    if(scc[u]&1) Min1[u]=0;
    if(scc[u]&2) Min2[u]=0;
}
void redfs(int u,pii dt){
    Min1[u]=min(Min1[u],dt.first);Min2[u]=min(Min2[u],dt.second);
    for(pii v:adj[u]){
        redfs(v.first,{Min1[u]+v.second,Min2[u]+v.second});
    }
}
long long Query(int s,int xs[],int t,int yt[]){
    vector<int> node;
    for(int i=0;i<s;i++){scc[xs[i]+1]+=1;node.push_back(xs[i]+1);}
    for(int i=0;i<t;i++){scc[yt[i]+1]+=2;node.push_back(yt[i]+1);}
    sort(node.begin(),node.end(),cmp);
    for(int i=0;i<(s+t-1);i++) node.push_back(lca(node[i],node[i+1]));
    sort(node.begin(),node.end(),cmp);
    node.erase(unique(node.begin(),node.end()),node.end());
    int root=-1;vector<int> v;
    for(int x:node){
        while(!v.empty() && R[v.back()]<L[x]) v.pop_back();
        if(!v.empty()) adj[v.back()].push_back({x,dep[x]-dep[v.back()]});
        else root=x;
        v.push_back(x);
    }
    dfs2(root);redfs(root,{inf,inf});
    ll res=inf;
    for(int x:node) res=min(res,Min1[x]+Min2[x]);
    for(int x:node){scc[x]=0;adj[x].clear();Min1[x]=Min2[x]=0;}
    return res;
}
void Init(int N, int A[],int B[],int D[]) {
    n=N;
    for(ll i=0;i<n-1;i++){
        edge[A[i]+1].push_back({B[i]+1,D[i]});
        edge[B[i]+1].push_back({A[i]+1,D[i]});
    }
    dfs(1,0);build_sparse();
}
