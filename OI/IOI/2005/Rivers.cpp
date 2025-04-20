#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 105;
const int inf = 1e18;
int n,k,w[maxn],d[maxn],total;
vector<pii> edge[maxn];
int f[maxn][maxn],g[maxn][maxn];

void dfs2(int u,int x){
    for(int i=0;i<=k;i++) g[u][i]=0;
    //cout << "dfs2 " << u << ' ' << x << endl;
    for(auto [v,t]:edge[u]){
        dfs2(v,x);
        for(int i=k;i>=0;i--) for(int j=0;j<=k-i;j++) g[u][i+j]=max(g[u][i+j],g[u][i]+g[v][j]);
    }
    for(int i=1;i<=k;i++) g[u][i]=max(g[u][i],f[u][i]+(d[u]-d[x])*w[u]);
    //cout << "dfs2 " << u << ' ' << x << '\n';
    //for(int i=0;i<=k;i++) cout << g[u][i] << ' ';
    //cout << '\n';
}

void dfs(int u){
    for(auto [v,x]:edge[u]){
        d[v]=d[u]+x;
        dfs(v);
        w[u]+=w[v];
        total+=w[v]*x;
    }
    dfs2(u,u);
    for(int i=0;i<k;i++) f[u][i+1]=g[u][i];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        int p,x;cin >> w[i] >> p >> x;
        edge[p].push_back({i,x});
    }
    k++;dfs(0);
    cout << total-f[0][k] << '\n';
}
