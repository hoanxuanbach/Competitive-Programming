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

#define ld long double

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    
    vector<int> b(m);
    vector<ld> c(m);
    vector<vector<pii>> g(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v >> b[i] >> c[i];
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }

    vector<ld> res(n+1,0);
    for(int s=1;s<=n;s++){
        vector<int> ord;
        vector<vector<pii>> f(n+1);

        vector<int> d(n+1,inf);
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        pq.push({d[s]=0,s});
        while(!pq.empty()){
            auto [dd,u]=pq.top();pq.pop();
            if(d[u]!=dd) continue;
            ord.push_back(u);
            for(auto [v,id]:g[u]){
                if(d[v]>d[u]+b[id]) f[v].clear(),pq.push({d[v]=d[u]+b[id],v});
                if(d[v]==d[u]+b[id]) f[v].push_back({u,id});
            }
        }

        vector<ld> total(n+1,0);
        vector<vector<pii>> h(n+1);
        total[s]=1;
        for(int u:ord) for(auto [v,id]:f[u]){
            h[v].push_back({u,id});
            total[u]+=c[id]*total[v];
        }

        vector<ld> val(n+1);
        for(int i=n-1;i>=0;i--){
            int u=ord[i];
            for(auto [v,id]:h[u]) val[u]+=c[id]*val[v];
            if(u!=s) res[u]+=a[s]*total[u]*val[u];
            val[u]+=a[u]/total[u];
        }
    }
    for(int i=1;i<=n;i++) cout << setprecision(6) << fixed << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
