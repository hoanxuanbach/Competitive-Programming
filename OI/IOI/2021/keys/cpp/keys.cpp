#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5+5;
struct DSU{
    int p[maxn];
    void init(int n){
        for(int i=0;i<n;i++) p[i]=i;
    }
    int findpar(int u){
        if(p[u]!=u) return p[u]=findpar(p[u]);
        return u;
    }
}dsu;

std::vector<int> find_reachable(std::vector<int> T, std::vector<int> U, std::vector<int> V, std::vector<int> C) {
	int n=(int)T.size(),m=(int)U.size();
    vector<vector<int>> edge(n);
    for(int i=0;i<m;i++){
        edge[U[i]].push_back(i);
        edge[V[i]].push_back(i);
    }
    int mn=n;
    vector<int> ans;

    dsu.init(n);
    vector<int> d(n);
    while(true){
        vector<int> vis(n),a(n),res,cc;
        vector<vector<int>> f(n);

        bool cn=false;
        auto bfs = [&](int s){
            cn=true;
            for(int u:res) a[T[u]]=0;
            for(int x:cc) f[x].clear();
            res.clear();cc.clear();

            queue<int> q;q.push(s);
            while(!q.empty()){
                int u=q.front();q.pop();
                if(s!=dsu.findpar(u)){
                    vis[dsu.findpar(u)]=1;
                    dsu.p[s]=dsu.findpar(u);
                    return;
                }
                if(vis[u]) continue;
                vis[u]=1;res.push_back(u);
                if(!a[T[u]]){
                    a[T[u]]=1;
                    for(int v:f[T[u]]) q.push(v);
                }
                for(int id:edge[u]){
                    int v=u^U[id]^V[id];
                    if(a[C[id]]) q.push(v);
                    else f[C[id]].push_back(v),cc.push_back(C[id]);
                }
            }
            d[s]=1;
            if((int)res.size()<mn) ans=res,mn=(int)res.size();
            else if((int)res.size()==mn) for(int u:res) ans.push_back(u);
        };
        for(int i=0;i<n;i++) if(dsu.findpar(i)==i && !vis[i] && !d[i]) bfs(i);
        if(!cn) break;
    }
    vector<int> ret(n);
    for(int u:ans) ret[u]=1;
	return ret;
}
