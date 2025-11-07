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
    int n,m;cin >> n >> m;

    int T=n,res=0;
    vector<int> p(2*n);
    iota(p.begin(),p.end(),0);
    vector<int> pp(2*n),d(2*n),f(2*n,inf);

    function<int(int)> fp = [&](int u){
        if(u!=p[u]) return p[u]=fp(p[u]);
        return u;
    };
    auto unite = [&](int u,int v,int w){
        u=fp(u);v=fp(v);
        if(u==v){
            f[u]=min(f[u],w);
            return;
        }
        T++;
        pp[u]=T;pp[v]=T;
        p[u]=T;p[v]=T;f[T]=w;
    };
    for(int i=0;i<m;i++){
        int u,v,w;cin >> u >> v >> w;
        unite(u,v,w);res+=w;
        d[u]^=1;d[v]^=1;
    }
    for(int i=T-1;i>=1;i--) f[i]=min(f[i],f[pp[i]]);
    for(int i=1;i<=T;i++){
        if(d[i]==2) d[i]=0,res+=f[i];
        if(i<T) d[pp[i]]+=d[i];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
