#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    int n;cin >> n;
    vector<vector<int>> g(n+1);
    for(int i=2;i<=n;i++){
        int x;cin >> x;
        g[x].push_back(i);
    }
    vector<int> f(n+1),val(n+1,-inf),sz(n+1);
    vector<vector<pii>> S(n+1);
    function<void(int)> dfs = [&](int u){
        sz[u]=1;
        for(int v:g[u]){
            dfs(v);sz[u]+=sz[v];
            S[u].push_back({f[v],v});
        }
        sort(S[u].begin(),S[u].end(),greater<pii>());

        //cout << "dfs " << u << '\n';
        int cur=-inf;
        for(int i=0;i<(int)S[u].size();i++){
            int v=S[u][i].second;
            val[v]=max(val[v],cur);
            //cout << '*' << v << ' ' << cur << '\n';
            cur=max(cur,S[u][i].first+2*i+1);
        }
        f[u]=max(cur,0LL);
        cur=-inf;
        for(int i=(int)S[u].size()-1;i>=0;i--){
            int v=S[u][i].second;
            val[v]=max(val[v],cur);
            //cout << '*' << v << ' ' << val[v] << '\n';
            cur=max(cur,S[u][i].first+2*i-1);           
        }
    };
    dfs(1);

    vector<int> ans(n+1);
    function<void(int,int)> redfs = [&](int u,int cur){
        ans[u]=max(0LL,cur);
        vector<int> T;
        for(int v:g[u]) if(sz[v]!=1) T.push_back(f[v]);
        sort(T.begin(),T.end(),greater<int>());
        for(int i=0;i<T.size();i++) ans[u]=max(ans[u],T[i]+2*i+1);
        for(int v:g[u]) redfs(v,max(cur,val[v])+1);
    };
    redfs(1,-inf);

    for(int i=1;i<=n;i++) cout << ans[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
