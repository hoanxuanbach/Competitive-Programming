#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+5;
const int inf = 1e18;

int n;
struct node{
    int S=0,T=0;
    node(){}
    friend node operator+(node a,node b){
        a.T+=(2*a.S+1)*b.S+b.T;
        a.S+=b.S;
        return a;
    };
    friend node operator-(node a,node b){
        a.S-=b.S;
        a.T-=(2*a.S+1)*b.S+b.T;
        return a;
    }
}dp[maxn];
vector<int> edge[maxn];
int res=inf;

void dfs(int u,int p){
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        dp[u]=dp[u]+dp[v];
    }
    dp[u].S++;
}
void dfs2(int u,int p,node d){
    dp[u].S--;
    dp[u]=dp[u]+d;
    res=min(res,dp[u].T);
    for(int v:edge[u]){
        if(v==p) continue;
        node cc=dp[u]-dp[v];cc.S++;
        dfs2(v,u,cc);
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
    dfs2(1,0,node());
    cout << res << '\n';
}
