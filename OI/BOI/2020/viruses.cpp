#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 105;
const int inf = 1e18;
typedef array<int,4> node; 

int N,M,K;
int g[maxn][maxn],S;
int nxt[maxn][2],par[maxn],T;
int a[maxn],b[maxn][maxn];

int f[maxn][maxn][maxn],dp[maxn][maxn][maxn];


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> M >> K;
    for(int i=0;i<M;i++){
        int x,sz,u=0;
        cin >> x >> sz;
        for(int j=0;j<sz;j++){
            int y;cin >> y;
            if(!g[u][y]) g[u][y]=++S;
            u=g[u][y];
        }
        b[u][x]=1;
    }
    for(int i=0;i<K;i++){
        int sz,u=0;cin >> sz;
        for(int j=0;j<sz;j++){
            int y;cin >> y;
            if(!nxt[u][y]) nxt[u][y]=++T;
            u=nxt[u][y];
        }
        a[u]=1;
    }

    queue<int> q;q.push(0);
    while(!q.empty()){
        int u=q.front(),p=par[u];
        q.pop();a[u]|=a[p];
        for(int i=0;i<=1;i++){
            if(nxt[u][i]){
                int v=nxt[u][i];
                par[v]=(u?nxt[p][i]:0);
                q.push(v);
            }
            else nxt[u][i]=nxt[p][i];
        }
    }
    for(int i=0;i<N;i++) for(int x=0;x<=T;x++) for(int y=0;y<=T;y++) f[i][x][y]=inf;
    for(int i=0;i<=S;i++) for(int x=0;x<=T;x++) for(int y=0;y<=T;y++) dp[i][x][y]=inf;
    
    for(int x=0;x<=T;x++){
        for(int i=0;i<=1;i++){
            int y=nxt[x][i];
            if(!a[x] && !a[y]) f[i][x][y]=1;
        }
    }
    
    priority_queue<node,vector<node>,greater<node>> pq;
    for(int x=0;x<=T;x++) pq.push({dp[0][x][x]=0,0,x,x});
    while(!pq.empty()){
        auto [d,u,x,y]=pq.top();pq.pop();
        if(dp[u][x][y]!=d) continue;
        for(int i=0;i<N;i++) if(b[u][i] && f[i][x][y]>d){
            f[i][x][y]=d;
            for(int j=0,v;j<=S;j++) if(v=g[j][i]){
                for(int z=0;z<=T;z++) if(dp[v][z][y]>dp[j][z][x]+d) pq.push({dp[v][z][y]=dp[j][z][x]+d,v,z,y});
            }
        }
        for(int i=0,v;i<N;i++) if(v=g[u][i]){
            for(int z=0;z<=T;z++) if(dp[v][x][z]>d+f[i][y][z]) pq.push({dp[v][x][z]=d+f[i][y][z],v,x,z});
        }
    }
    for(int i=2;i<N;i++){
        int res=*min_element(f[i][0],f[i][0]+T+1);
        if(res!=inf) cout << "NO " << res << '\n';
        else cout << "YES\n";
    }
}