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
    int n,K;cin >> n >> K;

    int total=0;
    vector<int> w(n+1),c(n+1,K),s(n+1);
    for(int i=1;i<=n;i++) cin >> w[i],total+=max(w[i],0LL);
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool check=true;
    function<void(int,int)> dfs = [&](int u,int p){
        s[u]=max(w[u],0LL);
        for(int v:g[u]) if(v!=p){
            dfs(v,u);
            s[u]+=max(w[v],0LL);
        }
        if(s[u]>K){
            check=false;
            return;
        }
        int d=K-s[u];
        for(int v:g[u]) if(v!=p && w[v]==-1){
            int k=min(d,c[v]);
            d-=k;total+=k;
        }
        if(w[u]==-1) c[u]=d;
    };
    dfs(1,0);
    if(w[1]==-1) total+=c[1];
    cout << (check?total:-1) << '\n';
}

 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
