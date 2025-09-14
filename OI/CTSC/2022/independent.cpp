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
    int n;cin >> n;
    vector<int> d(n+1);
    for(int i=1;i<=n;i++) cin >> d[i];
    vector<vector<int>> G(n+1);    
    for(int i=2;i<=n;i++){
        int x;cin >> x;
        G[x].push_back(i);
    }

    vector<array<int,2>> a(n+1),f(n+1),g(n+1),h(n+1);
    function<void(int)> dfs = [&](int u){
        array<int,2> S={0,0};
        for(int v:G[u]){
            dfs(v);
            S[0]+=max({f[v][0],h[v][0],h[v][1]});
            S[1]+=max({f[v][1],h[v][0],h[v][1]});
        }
        g[u]={-d[u]+S[0],d[u]+S[1]};

        S={0,0};
        for(int v:G[u]){
            a[v][0]=max({f[v][0],g[v][0],g[v][1],h[v][0],h[v][1]});
            a[v][1]=max({f[v][1],g[v][0],g[v][1],h[v][0],h[v][1]});
            S[0]+=a[v][0],S[1]+=a[v][1];
        }
        f[u]={d[u]+max(S[0],S[1]),-d[u]+max(S[0],S[1])};

        h[u]={-inf,-inf};
        for(int v:G[u]){
            S[0]-=a[v][0],S[1]-=a[v][1];
            int val=max(d[u]+max(g[v][0],h[v][0]),-d[u]+max(g[v][1],h[v][1]));
            h[u][0]=max(h[u][0],val+S[0]),h[u][1]=max(h[u][1],val+S[1]);
            S[0]+=a[v][0],S[1]+=a[v][1];
        }
    };
    dfs(1);
    int res=max({g[1][0],g[1][1],h[1][0],h[1][1]});
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
