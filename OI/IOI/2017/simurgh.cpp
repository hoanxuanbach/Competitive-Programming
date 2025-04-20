#include "simurgh.h"
#include<bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> par;
    DSU(int n=0){
        par.assign(n,0);
        iota(par.begin(),par.end(),0);
    }
    int findpar(int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    }
    bool unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u!=v) par[v]=u;
        return (u!=v);
    }
};

std::vector<int> find_roads(int n, std::vector<int> U, std::vector<int> V) {
    vector<vector<int>> edge(n);
    int m=(int)U.size();
    for(int i=0;i<m;i++){
        edge[U[i]].push_back(i);
        edge[V[i]].push_back(i);
    }
    int T=0;
    vector<int> vis(n);
    vector<int> up(n,-1),d(n),f(n,1);
    vector<vector<int>> cc(n);
    function<void(int,int)> dfs = [&](int u,int p){
        vis[u]=++T;
        vector<int> nw;
        for(int id:edge[u]){
            int v=U[id]^V[id]^u;
            if(v==p) continue;
            if(!vis[v]){
                //cout << "edge " << u << ' ' << v << endl;
                nw.push_back(v);
                up[v]=id;
                d[v]=d[u]+1;
                dfs(v,u);
            }
            else if(vis[v]<vis[u]) cc[u].push_back(id);
        }
        edge[u]=nw;
    };
    dfs(0,0);
    function<void(int)> build = [&](int u){
        for(int v:edge[u]){
            d[v]=d[u]+!vis[v];
            build(v);
        }
    };
    vis.assign(n,0);
    for(int s=1;s<n;s++){
        for(int id:cc[s]){
            int v=U[id]^V[id]^s;
            if(d[s]==d[v]) continue;
            vector<bool> incycle(n);
            vector<int> cycle,other;
            {
                int u=s;
                while(u!=v){
                    incycle[u]=true;
                    cycle.push_back(u);
                    u^=U[up[u]]^V[up[u]];
                }
            }
            for(int i=1;i<n;i++) if(!incycle[i]) other.push_back(up[i]);
            auto get = [&](int x){
                vector<int> cur=other;
                for(int u:cycle) if(u!=x) cur.push_back(up[u]);
                if(x!=-1) cur.push_back(id);
                return count_common_roads(cur);
            };
            int x=-1;
            for(int u:cycle) if(vis[u]) x=u;
            if(x!=-1){
                int val=get(x);
                for(int u:cycle) if(!vis[u]) f[u]=f[x]^(val!=get(u));
            }
            else{
                int val=get(-1),sz=(int)cycle.size();
                vector<int> cnt(sz);
                for(int i=0;i<sz;i++) cnt[i]=get(cycle[i]),val=max(val,cnt[i]);
                for(int i=0;i<sz;i++) f[cycle[i]]=(cnt[i]!=val);
            }
            for(int u:cycle) vis[u]=1;
            build(0);
        }
    }
    vector<int> ans;
    //for(int i=1;i<n;i++) cout << f[i] << ' ';
    //cout << '\n';
    for(int i=0;i<n;i++) edge[i].clear();
    for(int i=0;i<m;i++){
        edge[U[i]].push_back(i);
        edge[V[i]].push_back(i);
    }
    for(int u=0;u<n;u++){
        auto query = [&](int l,int r){
            vector<int> cur;
            DSU dsu(n);
            for(int i=l;i<r;i++){
                int id=edge[u][i];
                cur.push_back(id);
                int v=u^U[id]^V[id];
                dsu.unions(u,v);
            }
            int add=0;
            for(int i=1;i<n;i++){
                int id=up[i];
                if(dsu.unions(U[id],V[id])){
                    cur.push_back(id);
                    add+=f[i];
                }
            }
            return count_common_roads(cur)-add;
        };
        vector<int> cur;
        for(int id:edge[u]){
            int v=u^U[id]^V[id];
            if(v>u) cur.push_back(id);
        }
        edge[u]=cur;
        int sz=(int)edge[u].size(),total=query(0,sz);
        int l=0,r=sz;
        while(total--){
            int s=l;
            l++;r=sz;
            while(l<r){
                int mid=(l+r)>>1;
                if(query(s,mid)) r=mid;
                else l=mid+1;
            }
            ans.push_back(edge[u][l-1]);
        }
    }
    return ans;
}
