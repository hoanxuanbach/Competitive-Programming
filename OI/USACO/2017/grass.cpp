//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define pii pair<int,int>
struct ed{
    int u,v,w;
    bool operator<(ed o){return w<o.w;}
};
int par[maxn],r[maxn],c[maxn],n,m,k,q,p[maxn],len[maxn],t[maxn];
vector<pii> edge[maxn];
priority_queue<int,vector<int>,greater<int>> pq;
map<int,set<int>> mp[maxn];
vector<ed> e;
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v,int w){
    int pu=findpar(u),pv=findpar(v);
    if(pu==pv) return;
    if(r[pu]>=r[pv]){par[pv]=pu;r[pu]+=r[pv];}
    else{par[pu]=pv;r[pv]+=r[pu];}
    edge[u].push_back({v,w});
    edge[v].push_back({u,w});
}
void dfs(int u,int pr){
    p[u]=pr;
    for(pii v:edge[u]){
        if(v.first==pr) continue;
        dfs(v.first,u);len[v.first]=v.second;
        mp[u][t[v.first]].insert(v.second);
    }
    for(auto it:mp[u]){
        if(it.first!=t[u]) pq.push(*it.second.begin());
    }
}
signed main(){
    freopen("grass.in","r",stdin);
    freopen("grass.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //auto st=clock();
    cin  >> n >> m >> k >> q;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        e.push_back({u,v,w});
    }
    for(int i=1;i<=n;i++){cin >> t[i];par[i]=i;r[i]=1;}
    sort(e.begin(),e.end());
    for(int i=0;i<(int)e.size();i++) unions(e[i].u,e[i].v,i);
    dfs(1,0);
    for(int i=1;i<=q;i++){
        int u,x;cin >> u >> x;
        if(!mp[u][t[u]].empty()) pq.push(*mp[u][t[u]].begin());
        int pu=p[u];
        if(pu!=0){
            mp[pu][t[u]].erase(len[u]);
            if(t[pu]!=t[u] && !mp[pu][t[u]].empty()) pq.push(*mp[pu][t[u]].begin());
            mp[pu][x].insert(len[u]);
            if(t[pu]!=x && !mp[pu][x].empty()) pq.push(*mp[pu][x].begin());
        }
        t[u]=x;
        while(t[e[pq.top()].u]==t[e[pq.top()].v]) pq.pop();
        cout << e[pq.top()].w << '\n';
    }
    //cout << "TIME: " << (clock()-st) << "ms\n";
}
