#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
#define pii pair<int,int>
const int mod=998244353;
const int inf=1e18;
int n,m,q,dp[maxn],b[maxn],a[maxn];
vector<pii> edge[maxn],adj[maxn];
multiset<int> s[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++){
        for(pii v:edge[i]){
            if((int)edge[v.first].size()>100) adj[i].push_back({v.first,v.second});
        }
    }
    for(int i=1;i<=q;i++) cin >> b[i];
    for(int i=1;i<=n;i++){
        if((int)edge[i].size()<=100){
            for(pii v:edge[i]) s[v.first].insert(v.second);
        }
    }
    for(int i=q;i>=1;i--){
        int x=b[i],pre=dp[x];dp[x]=inf;
        if(!s[x].empty()) dp[x]=min(dp[x],*s[x].begin());
        for(pii v:adj[x]) dp[x]=min(dp[x],dp[v.first]+v.second);
        if((int)edge[x].size()<=100){
            for(pii v:edge[x]){
                auto it=s[v.first].lower_bound(pre+v.second);
                s[v.first].erase(it);s[v.first].insert(dp[x]+v.second);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=(ans+dp[i]%mod*a[i])%mod;
    cout << ans << '\n';
}