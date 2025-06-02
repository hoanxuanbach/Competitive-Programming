#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int maxm = 2e5+5;

int deg[maxn];
bool del[maxm];
pair<int,int> E[maxm];

bool vis[maxn];
vector<pair<int,int>> edge[maxn];

void dfs(int u){
    vis[u]=true;
    for(auto[v,id]:edge[u]){
        if(vis[v]) continue;
        dfs(v);
        if(deg[v]) del[id]=true;
        deg[u]^=deg[v];
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    int n,m;cin >> n >> m;
    for(int i=1;i<=n;i++) deg[i]=1;
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
        deg[u]^=1;deg[v]^=1;
        E[i]={u,v};
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);

    for(int i=1;i<=n;i++) deg[i]=0;

    int cnt=0;
    vector<pair<int,int>> ans;
    for(int i=0;i<m;i++){
        if(del[i]){
            ans.push_back(E[i]);
            continue;
        }
        auto [u,v]=E[i];
        deg[u]^=1;deg[v]^=1;
    }
    for(int i=1;i<=n;i++) cnt+=deg[i];

    cout << cnt << '\n';
    cout << (int)ans.size() << '\n';
    for(auto [u,v]:ans) cout << u << ' ' << v << '\n';
}
