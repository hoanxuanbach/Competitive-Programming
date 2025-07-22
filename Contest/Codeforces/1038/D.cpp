#include<bits/stdc++.h>
using namespace std; 
//#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e9;
const int maxn = 5e3+5;

int dp[2][maxn];
vector<int> edge[maxn];

void solve(){   
    int n,m;cin >> n >> m;
    for(int i=1;i<=n;i++) edge[i].clear();
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    for(int i=1;i<=n;i++) dp[0][i]=inf;
    dp[0][1]=0;


    int k=0;
    for(int t=0;t<2*n;t++){
        for(int i=1;i<=n;i++) dp[k^1][i]=inf;
        for(int i=1;i<=n;i++){
            int x=edge[i][t%(int)edge[i].size()];
            dp[k^1][x]=min(dp[k^1][x],dp[k][i]);
            dp[k^1][i]=min(dp[k^1][i],dp[k][i]+1);
        }
        k^=1;
        if(dp[k][n]!=inf){
            cout << t+1 << ' ' << dp[k][n] << '\n';
            return;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}