#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,m,q;
    cin >> n >> m >> q;
    vector<pair<int,int>> E(m);
    vector<vector<pair<int,int>>> g(n);

    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        E[i]={u,v};
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }
    for(int i=0;i<n;i++) sort(g[i].begin(),g[i].end());

    vector<int> f(q,-1);
    vector<pair<int,int>> P(q);

    int x=1,y=0,z=1;
    for(int i=0;i<q;i++){
        cin >> P[i].first >> P[i].second;
        P[i].first=(P[i].first+x+n-1)%n;
        P[i].second=(P[i].second+y+n)%n;
        x=x*2%n;y=(y+z)%n;z=z*3%n;
        int pos=lower_bound(g[P[i].first].begin(),g[P[i].first].end(),pii{P[i].second,0})-g[P[i].first].begin();
        if(pos<(int)g[P[i].first].size() && g[P[i].first][pos].first==P[i].second) f[i]=g[P[i].first][pos].second;
        //cout << "edge " << P[i].first << ' ' << P[i].second << '\n';
    }

    vector<bool> del,vis;
    auto check = [&](int k){
        del.assign(m,false);
        vis.assign(n,false);
        for(int i=0;i<k;i++) if(f[i]!=-1) del[f[i]]=true;
        int cnt=0;
        function<void(int)> dfs = [&](int u){
            cnt++;vis[u]=true;
            for(auto [v,id]:g[u]) if(!del[id] && !vis[v]) dfs(v); 
        };
        dfs(0);
        //cout << k << ' ' << (cnt==n) << '\n';
        return (cnt==n);
    };

    int l=0,r=q,res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,l=mid+1;
        else r=mid-1;
    }
    for(int i=0;i<res;i++) cout << 1 << '\n';
    for(int i=res;i<q;i++) cout << 0 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
