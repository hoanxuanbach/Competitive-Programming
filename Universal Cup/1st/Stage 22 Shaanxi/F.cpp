#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int LG = 18;
void solve(){
    int n,m,k;cin >> n >> m >> k;

    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int T=0;
    vector<int> dd(n+1),L(n+1),R(n+1);
    vector<vector<int>> par(n+1,vector<int>(LG,0));

    function<void(int,int)> pre_dfs = [&](int u,int p){
        dd[u]=dd[p]+1;
        par[u][0]=p;
        for(int i=1;i<LG;i++) par[u][i]=par[par[u][i-1]][i-1];
        L[u]=++T;
        for(int v:g[u]) if(v!=p) pre_dfs(v,u);
        R[u]=T;
    };
    pre_dfs(1,0);

    auto jmp = [&](int u,int d){
        for(int i=0;i<LG;i++) if(d>>i&1) u=par[u][i];
        return u;
    };
    auto lca = [&](int u,int v){
        if(dd[u]>dd[v]) swap(u,v);
        for(int i=0;i<LG;i++) if((dd[v]-dd[u])>>i&1) v=par[v][i];
        if(u==v) return u;
        for(int i=LG-1;i>=0;i--) if(par[u][i]!=par[v][i]){
            u=par[u][i];
            v=par[v][i];
        }
        return par[u][0];
    };

    vector<vector<array<int,3>>> f(n+1);
    for(int i=0;i<m;i++){
        int a,b,w;cin >> a >> b >> w;
        f[lca(a,b)].push_back({a,b,w});
    }

    vector<int> bit(n+1);
    auto update = [&](int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    };
    auto query = [&](int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    };
    auto update_range = [&](int l,int r,int val){
        update(l,val);
        update(r+1,-val);
    };

    vector<int> dp(n+1);
    vector<int> id(n+1);
    function<void(int,int)> dfs = [&](int u,int p){

        vector<int> cur;
        for(int v:g[u]) if(v!=p){
            id[v]=(int)cur.size();
            cur.push_back(v);
            dfs(v,u);
        }
        int sz=(int)cur.size();
        vector<vector<int>> cost(sz,vector<int>(sz,-1));
        for(int v:cur) cost[id[v]][id[v]]=dp[v];
        for(auto [a,b,w]:f[u]){
            if(dd[a]>dd[b]) swap(a,b);

            int fa=-1,fb=-1;
            if(a!=u) fa=id[jmp(a,dd[a]-dd[u]-1)];
            if(b!=u) fb=id[jmp(b,dd[b]-dd[u]-1)];

            int val=w;
            if(fa!=-1) val+=query(L[a]);
            if(fb!=-1) val+=query(L[b]);
            
            if(fa==-1) fa=fb;
            if(fa<fb) swap(fa,fb);

            cost[fa][fb]=max(cost[fa][fb],val);
        }

        vector<int> cc(1<<sz,-1);
        
        cc[0]=0;
        for(int i=0;i<sz;i++){
            for(int mask=0;mask<(1<<i);mask++){
                for(int j=0;j<=i;j++) if(cost[i][j]!=-1 && !(mask>>j&1)) cc[mask|(1<<i)|(1<<j)]=max(cc[mask|(1<<i)|(1<<j)],cc[mask]+cost[i][j]);
            }
        }

        vector<int> val(sz,-1);
        for(int i=0;i<sz;i++) for(int j=0;j<(1<<sz);j++) if(!(j>>i&1)) val[i]=max(val[i],cc[j]);

        dp[u]=cc[(1<<sz)-1];
        for(int i=0;i<sz;i++) dp[u]=max(dp[u],val[i]),update_range(L[cur[i]],R[cur[i]],val[i]);
        update_range(L[u],L[u],dp[u]);
    };
    dfs(1,0);
    cout << dp[1] << '\n';
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}