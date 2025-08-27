#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1e9+7;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    int n,m,k;cin >> n >> m >> k;

    vector<int> ans(n+1);
    vector<bool> vis(n+1);
    vector<vector<pair<int,int>>> edge(n+1);
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }

    if(k==1){
        for(int i=1;i<=n;i++) cout << 1 << ' ';
        cout << '\n';
        for(int i=1;i<=n;i++) cout << '\n';
        return;
    }

    set<int> leaf;
    vector<set<pair<int,int>>> adj(n+1);
    vector<int> deg(n+1);

    auto add = [&](int u,int v,int id){
        if(deg[u]==1) leaf.erase(u);
        if(deg[v]==1) leaf.erase(v);    
        deg[u]++;deg[v]++;
        adj[u].insert({v,id});
        adj[v].insert({u,id});
        if(deg[u]==1) leaf.insert(u);
        if(deg[v]==1) leaf.insert(v);
    };

    auto del = [&](int u,int v,int id){
        if(deg[u]==1) leaf.erase(u);
        if(deg[v]==1) leaf.erase(v);    
        deg[u]--;deg[v]--;
        adj[u].erase({v,id});
        adj[v].erase({u,id});
        if(deg[u]==1) leaf.insert(u);
        if(deg[v]==1) leaf.insert(v);
    };
    
    int cnt=0;
    vector<pair<int,int>> trace(n+1,{-1,-1});
    function<void(int)> dfs = [&](int u){
        cnt++;
        vis[u]=true;
        if(cnt<=k) ans[u]=cnt;
        
        for(auto [v,id]:edge[u]) if(!vis[v]){
            int a=-1,b=-1,c=-1;
            if(cnt>=k){
                auto it=leaf.begin();
                if(*it==u) it=next(it);
                a=*it,b=adj[a].begin()->first,c=adj[a].begin()->second;
                del(a,b,c);
                ans[v]=ans[a];
            }
            add(u,v,id);
            trace[v]={c,id};
            dfs(v);
            if(c!=-1){del(u,v,id);add(a,b,c);}
        }
    };
    dfs(1);

    for(int i=1;i<=n;i++) cout << ans[i] << ' ';
    cout << '\n';
    
    vis.assign(n+1,false);
    vector<vector<int>> f(n+1);
    for(int i=1;i<=n;i++) if(trace[i].first==-1){
        if(trace[i].second!=-1) f[1].push_back(trace[i].second);
    }

    function<void(int)> trace_dfs = [&](int u){
        vis[u]=true;
        if(trace[u].first!=-1){
            f[u].erase(find(f[u].begin(),f[u].end(),trace[u].first));
            f[u].push_back(trace[u].second);
        }

        for(auto [v,id]:edge[u]){
            if(!vis[v]){
                f[v]=f[u];
                trace_dfs(v);
            }
        }
    };
    trace_dfs(1);

    for(int i=1;i<=n;i++){
        for(int id:f[i]) cout << id << ' ';
        cout << '\n';
    }
}