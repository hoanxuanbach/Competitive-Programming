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

const int L=26;
void solve(){
    int n;cin >> n;
    vector<vector<pair<int,int>>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int total=0;
    vector<int> d(n+1);
    vector<array<int,2>> c(n+1);

    for(int i=0;i<L;i++){
        int cnt=0;
        function<void(int,int)> dfs = [&](int u,int p){
            c[u]={0,0};
            c[u][d[u]]++;
            for(auto [v,w]:g[u]){
                if(v==p) continue;
                d[v]=d[u]^(w>>i&1);
                dfs(v,u);
                cnt+=c[v][0]*c[u][1]+c[u][0]*c[v][1];
                c[u][0]+=c[v][0];
                c[u][1]+=c[v][1];
            }
        };
        dfs(1,0);
        total+=(cnt<<i);
    }
    cout << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
