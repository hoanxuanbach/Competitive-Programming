#include<bits/stdc++.h>
using namespace std;
#define maxn 10005
int n,m,low[maxn],num[maxn],st[maxn],sz,pos,cnt,scc[maxn],in[maxn],out[maxn];
vector<int> edge[maxn];
bool vis[maxn],inst[maxn];
void dfs(int u){
    low[u]=num[u]=++pos;
    st[++sz]=u;vis[u]=inst[u]=true;
    for(int v:edge[u]){
        if(!vis[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(inst[v]) low[u]=min(low[u],num[v]);
    }
    if(low[u]==num[u]){
        cnt++;
        while(st[sz]!=u){
            int v=st[sz--];
            inst[v]=false;scc[v]=cnt;
        }
        scc[u]=cnt;inst[u]=false;sz--;
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs(i);
    }
    for(int i=1;i<=n;i++){
        for(int v:edge[i]){
            if(scc[i]==scc[v]) continue;
            out[scc[i]]++;
            in[scc[v]]++;
        }
    }
    if(cnt==1) cout << 0 << '\n';
    else{
        int s1=0,s2=0;
        for(int i=1;i<=cnt;i++){
            if(in[i]==0) s1++;
            if(out[i]==0) s2++;
        }
        cout << max(s1,s2) << '\n';
    }
}
