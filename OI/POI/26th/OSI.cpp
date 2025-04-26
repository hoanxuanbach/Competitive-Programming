#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define pii pair<int,int>
int n,m,low[maxn],num[maxn],cnt,ans,pos;
vector<pii> edge[maxn];
bool check[maxn],vis[maxn];
void dfs(int u,int p){
    vis[u]=true;low[u]=num[u]=++pos;
    for(pii v:edge[u]){
        if(abs(v.second)==p) continue;
        if(!vis[v.first]){
            dfs(v.first,abs(v.second));
            low[u]=min(low[u],low[v.first]);
            if(low[v.first]>num[u]) cnt++;
            if(v.second>0) check[abs(v.second)]=1;
            else check[abs(v.second)]=0;
        }
        else{
            low[u]=min(low[u],num[v.first]);
            if(num[u]>=num[v.first]){
                if(v.second>0) check[abs(v.second)]=1;
                else check[abs(v.second)]=0;
            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});
        edge[v].push_back({u,-i});
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            cnt=0;dfs(i,0);
            ans+=cnt+1;
        }
    }
    cout << ans << '\n';
    for(int i=1;i<=m;i++){
        if(check[i]) cout << '>';
        else cout << '<';
    }
}
