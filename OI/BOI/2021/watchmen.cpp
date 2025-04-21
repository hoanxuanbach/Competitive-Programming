#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 250005;
const int maxk = 1005;

int n,m,k,f[maxn],t[maxn],L[maxk];
vector<int> edge[maxn],dp[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) t[i]=-1;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    cin >> k;
    for(int i=1;i<=k;i++){
        cin >> L[i];
        for(int j=0;j<L[i];j++){
            int u;cin >> u;
            t[u]=j,f[u]=i;
        }
    }
    L[0]=1;
    for(int i=1;i<=n;i++) dp[i].assign(L[f[i]],inf);
    priority_queue<array<int,3>> pq;
    auto add = [&](int u,int d){
        int x=d%L[f[u]];
        if(x!=t[u] && d<dp[u][x]) pq.push({-(dp[u][x]=d),u,x});
    };
    add(1,0);
    while(!pq.empty()){
        auto [d,u,x]=pq.top();
        pq.pop();d*=-1;
        if(d!=dp[u][x]) continue;
        int a=f[u];
        for(int i=0;i<(int)edge[u].size();i++){
            int v=edge[u][i],b=f[v];
            if(!a || a!=b || (t[v]+1)%L[a]!=t[u] || t[v]!=x) add(v,d+1);
            if(!a && b) add(v,d+1+(t[v]+L[b]-d%L[b])%L[b]);
            bool del=false;
            if(a && b && (a!=b || ((t[u]+1)%L[a]!=t[v] && (t[v]+1)%L[a]!=t[u]))){
                int T=d+(t[v]+L[b]-d%L[b])%L[b];
                int T2=T+(t[u]+L[a]-T%L[a])%L[a];
                if(T!=T2){
                    add(v,T+1);
                    del=true;
                }
                else{
                    int nd=T+(x+L[a]-t[u])%L[a];
                    add(v,nd+1);
                    if(L[b]%L[a]!=0 && (L[a]%L[b]!=0 || (t[u]+L[a]-x)%L[a]>=L[b])) add(v,nd+1+(t[v]+L[b]-nd%L[b])%L[b]);
                }
            }
            if(!a || !b || del){
                swap(edge[u][i],edge[u].back());
                edge[u].pop_back();i--;
            }
        }

        add(u,d+1);
    }
    if(dp[n][0]==inf) cout << "impossible\n";
    else cout << dp[n][0] << '\n';
}