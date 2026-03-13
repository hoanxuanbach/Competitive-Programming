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
    int n,m,k;cin >> n >> m >> k;
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int a=n,b=0,res=1;
    auto f = [&](int x){
        int cur=0,val=1;
        for(int i=1;i<x;i++){
            val=val*(k-1)%mod;
            cur=(val+mod-cur)%mod;
        }
        return cur*k%mod;
    };

    vector<int> d(n+1);
    function<void(int,int)> dfs = [&](int u,int p){
        d[u]=d[p]+1;
        for(int v:g[u]){
            if(v==p) continue;
            if(!d[v]) dfs(v,u);
            else if(d[v]<d[u]){
                int s=d[u]-d[v]+1;a-=s;b++;
                res=res*f(s)%mod;
            }
        }
    };
    dfs(1,0);
    
    b+=a;
    for(int i=0;i<a;i++) res=res*k%mod;
    int invk=power(k,mod-2)%mod;
    for(int i=1;i<b;i++) res=res*(k-1)%mod*invk%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
