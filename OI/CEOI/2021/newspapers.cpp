#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;

bool f[maxn];
int n,m,d[maxn],dd[maxn],par[maxn];
vector<int> edge[maxn];

void dfs(int u,int p){
    d[u]=d[p]+1,par[u]=p;
    for(int v:edge[u]) if(v!=p) dfs(v,u);
}
void dfs2(int u,int p){
    dd[u]=0;
    for(int v:edge[u]) if(v!=p && !f[v]){
        dfs2(v,u);
        dd[u]=max(dd[u],dd[v]+1);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    if(m>=n){
        cout << "NO\n";
        return 0;
    }
    if(n==1){
        cout << "YES\n1\n1\n";
        return 0;
    }
    else if(n==2){
        cout << "YES\n2\n1 1\n";
        return 0;
    }
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    int Y=max_element(d+1,d+n+1)-d;
    dfs(Y,0);
    int X=max_element(d+1,d+n+1)-d;
    
    vector<int> path;
    for(int u=par[X];u!=Y;u=par[u]) path.push_back(u),f[u]=true;
    f[X]=f[Y]=true;
    
    vector<int> ans;
    for(int u:path){
        dfs2(u,0);
        if(dd[u]>2){
            cout << "NO\n";
            return 0;
        }
        for(int v:edge[u]) if(!f[v] && dd[v]) ans.push_back(u),ans.push_back(v);
        ans.push_back(u);
    }
    cout << "YES\n";
    cout << 2*(int)ans.size() << '\n';
    for(int u:ans) cout << u << ' ';
    reverse(ans.begin(),ans.end());
    for(int u:ans) cout << u << ' ';
    cout << '\n';
}