#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 1000005
int n,w[maxn],dp[maxn][2],sum[maxn],Max2[maxn][2];
vector<int> edge[maxn],ans;
void dfs(int u,int par){
    dp[u][0]=dp[u][1]=Max2[u][0]=Max2[u][1]=0;sum[u]=0;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);sum[u]+=w[v];
        if(dp[v][1]>dp[u][0]){
            Max2[u][0]=dp[u][0];
            dp[u][0]=dp[v][1];
        }
        else if(dp[v][1]>Max2[u][0]) Max2[u][0]=dp[v][1];
        if(dp[v][0]-w[v]>dp[u][1]){
            Max2[u][1]=dp[u][1];
            dp[u][1]=dp[v][0]-w[v];
        }
        else if(dp[v][0]-w[v]>Max2[u][1]) Max2[u][1]=dp[v][0]-w[v];
    }
    dp[u][1]+=sum[u];dp[u][0]+=w[u];
}
void rev_dfs(int u,int par,int f0,int f1){
    dp[u][1]-=sum[u];dp[u][0]-=w[u];
    for(int v:edge[u]){
        if(v==par) continue;
        int nxt0,nxt1;
        if(dp[v][1]==dp[u][0]) nxt0=Max2[u][0];
        else nxt0=dp[u][0];
        if(dp[v][0]-w[v]==dp[u][1]) nxt1=Max2[u][1];
        else nxt1=dp[u][1];
        rev_dfs(v,u,max(nxt0,f1)+w[u],max(nxt1,f0-w[par])+sum[u]-w[v]+w[par]);
    }
    dp[u][0]+=w[u];dp[u][1]+=sum[u];
    dp[u][0]=max(dp[u][0],f1+w[u]);
}
void trace(int u,int par,int t){
    ans.push_back(u);
    if(t==0){
        for(int v:edge[u]){
            if(v==par) continue;
            if(dp[v][1]==dp[u][0]-w[u]) trace(v,u,1);
        }
    }
    else{
        int id=-1;
        for(int v:edge[u]){
            if(v==par) continue;
            if(dp[v][0]-w[v]==dp[u][1]-sum[u]){id=v;break;}
        }
        for(int v:edge[u]){
            if(v==par || v==id) continue;
            ans.push_back(v);ans.push_back(u);
        }
        if(id!=-1) trace(id,u,0);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> w[i];
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    /*
    n=4;
    for(int i=1;i<=n;i++) w[i]=1;
    for(int i=1;i<n;i++){
        edge[1].push_back(i+1);
        edge[i+1].push_back(1);
    }
    */
    dfs(1,0);
    rev_dfs(1,0,0,0);
    int id=0;
    for(int i=1;i<=n;i++){
        if(dp[i][0]>dp[id][0]) id=i;
    }
    cout << dp[id][0] << '\n';
    dfs(id,0);trace(id,0,0);
    if((int)ans.size()%2==0) ans.pop_back();
    cout << (int)ans.size()/2+1 << '\n';
    for(int v:ans) cout << v << ' ';
}
