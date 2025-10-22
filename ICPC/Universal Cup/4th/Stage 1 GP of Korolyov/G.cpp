#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;cin >> n >> m;
    
    vector<int> d(n+1);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        d[v]++;
    }

    int cnt=0;
    queue<int> q;
    for(int i=1;i<=n;i++) if(!d[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();cnt++;
        for(int v:g[u]) if(!(--d[v])) q.push(v);
    }

    vector<int> sz(n+1);
    vector<set<int>> nxt(n+1),pre(n+1);
    for(int i=1;i<=n;i++) if(d[i]){
        sz[i]=1;
        for(int v:g[i]){
            nxt[i].insert(v);
            pre[v].insert(i);
        }
    }

    for(int i=1;i<=n;i++) if((int)pre[i].size()==1) q.push(i),d[i]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        int p=*pre[u].begin();
        if(p==u) continue;
        sz[p]+=sz[u];sz[u]=0;
        for(int v:nxt[u]){
            pre[v].erase(u);
            pre[v].insert(p);
            nxt[p].insert(v);
            if((int)pre[v].size()==1 && d[v]) q.push(v),d[v]=0;
        }
        nxt[p].erase(u);
    }

    int mx=0;
    for(int i=1;i<=n;i++) mx=max(mx,sz[i]);
    cout << cnt+mx << '\n';
}