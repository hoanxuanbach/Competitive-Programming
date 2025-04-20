#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6+5;
const int inf = 1e18;
int N,P[maxn],L[maxn],dp[maxn],mx[maxn],res;
int deg[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N;
    for(int i=1;i<=N;i++){
        cin >> P[i] >> L[i];
        deg[P[i]]++;
    }
    queue<int> q;
    for(int i=1;i<=N;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        int u=q.front(),p=P[u];q.pop();
        mx[p]=max({mx[p],mx[u],dp[p]+dp[u]+L[u]});
        dp[p]=max(dp[p],dp[u]+L[u]);
        if(!(--deg[p])) q.push(p);
    }
    for(int i=1;i<=N;i++){
        if(!deg[i]) continue;
        vector<int> cycle;
        int u=i,ans=0,total=0;
        while(deg[u]){
            ans=max(ans,mx[u]);
            total+=L[u];
            cycle.push_back(u);
            deg[u]=0;u=P[u];
        }
        int m1=-inf,m2=-inf;
        for(int v:cycle){
            ans=max({ans,m1+dp[v],m2+dp[v]+total});
            m1=max(m1,dp[v])+L[v];
            m2=max(m2,dp[v])-L[v];
        }
        res+=ans;
    }
    cout << res << '\n';
}
