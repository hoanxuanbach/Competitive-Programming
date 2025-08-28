#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define maxn 200005
int Max1[maxn],Max2[maxn],n,m,ans;
vector<pii> edge[maxn];
vector<int> x[maxn];
void dfs(int u,int par){
    for(pii v:edge[u]){
        if(v.first==par) continue;
        dfs(v.first,u);
        int ma=Max1[v.first]+v.second;
        x[u].push_back(ma);
        if(ma>Max1[u]){
            Max2[u]=Max1[u];
            Max1[u]=ma;
        }
        else if(ma>Max2[u]) Max2[u]=ma;
    }
}
void re_dfs(int u,int par,int d){
    x[u].push_back(d);x[u].push_back(0);x[u].push_back(0);
    for(pii v:edge[u]){
        if(v.first==par) continue;
        if(Max1[u]==Max1[v.first]+v.second) re_dfs(v.first,u,max(d,Max2[u])+v.second);
        else re_dfs(v.first,u,max(d,Max1[u])+v.second);
    }
    sort(x[u].begin(),x[u].end(),greater<int>());
    ans=max(ans,x[u][0]+x[u][2]+2*x[u][1]);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    dfs(1,0);re_dfs(1,0,0);
    cout << ans << '\n';
}