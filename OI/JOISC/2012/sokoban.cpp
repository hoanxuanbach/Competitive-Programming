#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 1e3+5;
const int maxT = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int dx[]={0,1,0,-1},
    dy[]={1,0,-1,0};

int n,m,X;
int f[maxn][maxn];
char c[maxn][maxn];

vector<int> edge[maxT];
void add_edge(int u,int v){
    edge[u].push_back(v);
    edge[v].push_back(u);
}

int num[maxT],low[maxT],par[maxT],T,sz[maxT];

void dfs(int u,int p){
    num[u]=low[u]=++T;
    par[u]=p,sz[u]=1;
    for(int v:edge[u]){
        if(v==p) continue;
        if(!num[v]){
            dfs(v,u);
            sz[u]+=sz[v];
            low[u]=min(low[u],low[v]);
        }
        else low[u]=min(low[u],num[v]);
    }
}

int bcnt;
bool vis[maxT];
vector<int> bcc[maxT];
void get_bcc(int u,int p,int id){
    if(id) bcc[u].push_back(id);
    vis[u]=true;
    for(int v:edge[u]){
        if(!vis[v]){
            if(low[v]>=num[u]){
                ++bcnt;
                bcc[u].push_back(bcnt);
                get_bcc(v,u,bcnt);
            }
            else get_bcc(v,u,id);
        }
    }
}
bool check(int x,int y){
    for(int i:bcc[x]) for(int j:bcc[y]) if(i==j) return true;
    return false;
}
bool valid(int x,int y){
    return (x>0 && x<=n && y>0 && y<=m && c[x][y]!='#');
}

bool ins[maxn][maxn][4];
void dfs2(int x,int y,int t){
    int xt=x+dx[t],yt=y+dy[t];
    ins[x][y][t]=true;
    //cout << x << ' ' << y << ' ' << t << '\n';
    for(int i=0;i<4;i++) if(i!=t && !ins[x][y][i]){
        int nx=x+dx[i],ny=y+dy[i];
        if(valid(nx,ny) && check(f[xt][yt],f[nx][ny])) dfs2(x,y,i);
    }

    int nx=xt+dx[t],ny=yt+dy[t];
    if(valid(nx,ny) && !ins[xt][yt][t]) dfs2(xt,yt,t); 
}

void solve(){   
    cin >> n >> m;

    int sx=-1,sy=-1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        cin >> c[i][j];
        if(c[i][j]=='X') sx=i,sy=j;
        if(c[i][j]!='#'){
            f[i][j]=++X;
            if(i>1 && c[i-1][j]!='#') add_edge(f[i-1][j],f[i][j]);
            if(j>1 && c[i][j-1]!='#') add_edge(f[i][j-1],f[i][j]);
        }
    }

    int root=f[sx][sy];
    dfs(root,0);
    get_bcc(root,0,0);

    for(int i=0;i<4;i++){
        int xt=sx+dx[i],yt=sy+dy[i];
        if(valid(xt,yt) && !ins[sx][sy][i]) dfs2(sx,sy,i);
    }

    int res=0;
    for(int x=1;x<=n;x++) for(int y=1;y<=m;y++) for(int i=0;i<4;i++) if(ins[x][y][i]){
        int u=f[x][y],v=f[x+dx[i]][y+dy[i]];
        if(par[v]==u) res+=sz[v];
        if(par[u]==v) res+=T-sz[u]-1;
    }
    cout << res-T+1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}