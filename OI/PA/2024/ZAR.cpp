#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
/*
const int maxn = 1e6+5;
int par[maxn],sz[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    par[v]=u;sz[u]+=sz[v];
}

vector<int> f[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,m;cin >> n >> m;
    vector<pair<int,int>> e(m);
    for(int i=0;i<m;i++) cin >> e[i].first >> e[i].second;
    for(int i=0;i<(1<<n);i++) par[i]=i,sz[i]=1;
    for(int mask=0;mask<(1<<n);mask++){
        for(auto [x,y]:e) if((mask>>x&1)==(mask>>y&1)) unions(mask,mask^(1<<x)^(1<<y));
    }
    for(int mask=0;mask<(1<<n);mask++) f[findpar(mask)].push_back(mask);
    for(int mask=0;mask<(1<<n);mask++){
        if(f[mask].empty()) continue;
        cout << (int)f[mask].size() << '\n';
        for(int x:f[mask]){
            for(int i=0;i<n;i++) cout << (x>>i&1);
            cout << '\n';
        }
    }
}
*/

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,m;cin >> n >> m;
    vector<int> d(n,-1),a(n);
    vector<vector<int>> edge(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;u--;v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int ans=1;
    for(int i=0;i<n;i++){
        if(d[i]!=-1) continue;
        bool check=false;
        int x=0,y=0;
        function<void(int)> dfs = [&](int u){
            x++;y+=(d[u]^a[u]);
            //cout << "dfs " << u << '\n';
            for(int v:edge[u]){
                if(d[v]==-1) d[v]=d[u]^1,dfs(v);
                else if(!(d[v]^d[u])) check=true;
            }
        };
        d[i]=0;dfs(i);
        //cout << check << ' ' << x << ' ' << y << '\n';
        if(check) ans=ans*power(2,x-1)%mod;
        else{
            for(int i=1;i<=y;i++) ans=ans*power(i,mod-2)%mod*(x-i+1)%mod;
        }
    }
    cout << ans << '\n';
}
