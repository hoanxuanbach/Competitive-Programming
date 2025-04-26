#include<bits/stdc++.h>
using namespace std;
#define maxn 3000005
vector<int> edge[maxn];
int cnt[maxn],d[maxn],dep[maxn],n,k,s;
void dfs(int u,int par){
    d[u]=d[par]+1;
    if(d[u]>d[s]) s=u;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);
    }
}
void dfs2(int u,int par){
    for(int v:edge[u]){
        if(v==par) continue;
        dfs2(v,u);
        dep[u]=max(dep[u],dep[v]+1);
    }
    if(u!=s) cnt[dep[u]]++;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);dfs2(s,0);
    int ans=0;
    for(int i=0;i<=n;i++){
        if(cnt[i]+1<=k){ans=i;break;}
    }
    cout << ans << ' ' << cnt[ans]+1 << '\n';
    cout << s << ' ';
    for(int i=1;i<=n;i++){
        if(dep[i]==ans) cout << i << ' ';
    }
    cout << '\n';
}
