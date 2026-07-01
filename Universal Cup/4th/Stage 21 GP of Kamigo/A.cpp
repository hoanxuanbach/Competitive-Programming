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
    int N,M,K;cin >> N >> M >> K;

    int cnt=0;
    map<pii,int> mp;
    vector<pii> E;
    for(int i=1;i<=K;i++){
        int x,y;cin >> x >> y;
        if(mp.find({x,0})==mp.end()) mp[{x,0}]=cnt++;
        if(mp.find({y,1})==mp.end()) mp[{y,1}]=cnt++;
        E.push_back({mp[{x,0}],mp[{y,1}]});
    }
    
    int cc=0;
    vector<vector<int>> g(cnt);
    for(auto [u,v]:E){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool odd=false;
    vector<int> vis(cnt);
    function<void(int)> dfs = [&](int u){
        for(int v:g[u]){
            if(vis[v]){
                if((vis[u]^vis[v])!=3) odd=true;
            }
            else{
                vis[v]=vis[u]^3;
                dfs(v);
            }
        }
    };
    for(int i=0;i<cnt;i++) if(!vis[i]){
        cc++;vis[i]=1;
        dfs(i);
    }
    int res=power(2,N*M-1-K-cnt+cc);
    if(!odd) res=res*2%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}