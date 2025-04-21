#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 1e9;
int n,c[maxn],dp[maxn][2][2];
vector<int> edge[maxn];

void dfs(int u,int p){
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) dp[u][i][j]=inf;
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
    }
    for(int x=0;x<=1;x++){
        array<int,2> f={0,inf};
        for(int v:edge[u]){
            if(v==p) continue;
            array<int,2> nf={inf,inf};
            for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) nf[i^j]=min(nf[i^j],f[i]+dp[v][x][j]);
            swap(f,nf);
        }   
        for(int i=0;i<=1;i++){
            int k=c[u]^i^x;
            dp[u][k][x]=min(dp[u][k][x],f[i]+x);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin >> c[i];
    dfs(1,0);
    int res=min(dp[1][0][0],dp[1][0][1]);
    if(res==inf) cout << "impossible\n";
    else cout << res << '\n';
}