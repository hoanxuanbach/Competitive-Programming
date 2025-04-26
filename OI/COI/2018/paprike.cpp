#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int n,k,h[maxn],num,dp[maxn];
vector<int> edge[maxn];
void dfs(int u,int par){
    int sum=h[u];
    vector<int> x;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);sum+=dp[v];
        x.push_back(dp[v]);
    }
    sort(x.begin(),x.end());
    while(sum>k){sum-=x.back();x.pop_back();num++;}
    dp[u]=sum;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >>h[i];
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    cout << num << '\n';
}
