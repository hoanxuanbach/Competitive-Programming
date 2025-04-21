#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 300005
int n,m,k,dp[maxn][(1<<5)+5],c[maxn];
vector<int> ms[10],edge[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++){cin >> c[i];c[i]--;dp[i][(1<<c[i])]=1;}
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int mask=0;mask<(1<<k);mask++){
        int cnt=0;
        for(int j=0;j<k;j++) cnt+=(mask>>j)&1;
        ms[cnt].push_back(mask);
    }
    int ans=0;
    for(int i=2;i<=k;i++){
        for(int mask:ms[i]){
            for(int j=1;j<=n;j++){
                if((mask^(1<<c[j]))==0) continue;
                for(int v:edge[j]) dp[j][mask]+=dp[v][mask^(1<<c[j])];
                ans+=dp[j][mask];
            }
        }
    }
    cout << ans << endl;
}
