#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int inf = 1e18;
const int mod = 998244353;
const int N = 4e5+5;

int n,c[N];
vector<int> g[N];

int sz[N],son[N];

int res[N];

void pre_dfs(int u,int p){
    sz[u]=1;son[u]=0;
    for(int v:g[u]){
        if(v==p) continue;
        pre_dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}

int S=0,D=0;
map<int,int> mp;

vector<pii> F[N];

int bit[2][2*N];

void del(int t,int x){
    x+=n+1;
    //assert(1<=x<=2*n+1);
    for(int i=x;i<=2*n+1;i+=(i&(-i))) bit[t][i]=-inf;
}
int query(int t,int x){
    //cout << "query " << t << ' ' << x << '\n';
    int val=-inf;x+=n+1;
    //assert(1<=x<=2*n+1);
    for(int i=x;i>=1;i-=(i&(-i))) val=max(val,bit[t][i]);
    return val;
}
void update(int t,int x,int val){
    //cout << "update " << t << ' ' << x << ' ' << val << '\n';
    x+=n+1;
    //assert(1<=x<=2*n+1);
    for(int i=x;i<=2*n+1;i+=(i&(-i))) bit[t][i]=max(bit[t][i],val);
}

void reset(){
    S=0;D=0;
    for(auto [y,x]:mp) del(0,y),del(1,-y);
    mp.clear();
}

int get(int a,int b){
    //cout << "get " << a << ' ' << b << '\n';
    int f0=query(0,-b-D);
    int f1=query(1,b+D);
    return max(f0+S+a+2*D+2*b,f1+S+a-2*D-2*b);
}
void add(int x,int y){
    //cout << "add " << x << ' ' << y << '\n';
    x-=S;y-=D;
    if(mp.find(y)==mp.end()) mp[y]=x;
    else mp[y]=max(mp[y],x);

    update(0,y,x+2*y);
    update(1,-y,x-2*y);

}

void dfs(int u,int p){
    res[u]=-1;
    F[u].clear();
    for(int v:g[u]){
        if(v==p || v==son[u]) continue;
        dfs(v,u);
        for(auto [x,y]:mp) F[v].push_back({y+S,x+D});
        reset();
    }
    if(son[u]){
        dfs(son[u],u);
        S++;D+=c[u];

        for(int v:g[u]){
            if(v==p || v==son[u]) continue;
            for(auto [x,y]:F[v]) res[u]=max(res[u],get(x,y));
            for(auto [x,y]:F[v]) add(x+1,y+c[u]);
        }
    }
    add(1,c[u]);
    res[u]=max(res[u],get(0,0));
    //cout << "res " << u << ' ' << res[u] << '\n';
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        char cc;cin >> cc;
        c[i]=(cc=='0'?1:-1);
        g[i].clear();
    }
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    pre_dfs(1,0);
    for(int i=0;i<=1;i++) for(int j=0;j<=2*n+1;j++) bit[i][j]=-inf;
    dfs(1,0);
    reset();
    for(int i=1;i<=n;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
