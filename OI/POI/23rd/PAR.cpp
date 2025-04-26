#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int n,res,dp[maxn];
vector<int> edge[maxn];

void dfs(int u,int p){
    int sz=(int)edge[u].size();
    dp[u]=sz;
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        res=max(res,dp[u]+dp[v]-2);
        dp[u]=max(dp[u],dp[v]-2+sz);
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
    dfs(1,0);
    cout << res << '\n';
}