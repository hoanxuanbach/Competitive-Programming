#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 1e18;
const int maxn = 505;

int n,a[maxn],sz[maxn];
vector<int> dp[maxn][maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp[i][j].clear();
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int total=0;
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;total+=a[u];
        dp[u][1].assign(n,0);
        for(int i=0;i<n;i++) dp[u][1][i]=a[u]*i;
        for(int v:g[u]){
            if(v==p) continue;
            dfs(v,u);
            for(int i=sz[u]+1;i<=sz[u]+sz[v];i++) dp[u][i].assign(n-i+1,inf);
            for(int i=sz[u];i>=1;i--){
                for(int t=0;t<(int)dp[u][i].size();t++){
                    int add=inf;
                    for(int j=1;j<=min(n-i-t,sz[v]);j++){
                        dp[u][i+j][t]=min(dp[u][i+j][t],dp[u][i][j+t]+dp[v][j][0]);
                        add=min(add,dp[v][j][i+t]);
                    }
                    dp[u][i][t]=min(inf,dp[u][i][t]+add);
                }
            }
            sz[u]+=sz[v];
        }
    };
    dfs(1,0);
    int res=inf;
    for(int i=1;i<=n;i++) res=min(res,dp[1][i][0]);
    cout << total+res << '\n';
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int test;cin >> test;
    while(test--) solve();
}