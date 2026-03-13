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
    vector<vector<char>> c(n,vector<char>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> c[i][j];
    
    int res=1,S=n*m;
    vector<int> p(S),sn(S),sm(S),g(S);
    iota(p.begin(),p.end(),0);
    for(int i=0;i<S;i++) sn[i]=1;

    function<int(int)> fp = [&](int u){
        if(u!=p[u]) return p[u]=fp(p[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        int flag=(u==v);
        u=fp(u);v=fp(v);
        if(u==v){
            sm[u]++;
            g[u]|=flag;
            return;
        }
        if(sn[u]<sn[v]) swap(u,v);
        sn[u]+=sn[v];
        sm[u]+=sm[v]+1;
        g[u]=g[u]|g[v];
        p[v]=u;
    };

    auto f = [&](int x,int y){
        return (x<0 || y<0 || x>=n || y>=m || c[x][y]=='*');
    };
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(c[i][j]=='*'){
        if(f(i-1,j) && f(i+1,j)) res=0;
        else if(f(i-1,j)) unite((i+1)*m+j,(i+1)*m+j);
        else if(f(i+1,j)) unite((i-1)*m+j,(i-1)*m+j);
        else unite((i-1)*m+j,(i+1)*m+j);

        if(f(i,j-1) && f(i,j+1)) res=0;
        else if(f(i,j-1)) unite(i*m+j+1,i*m+j+1);
        else if(f(i,j+1)) unite(i*m+j-1,i*m+j-1);
        else unite(i*m+j-1,i*m+j+1);
    }

    for(int i=0;i<S;i++) if(p[i]==i){
        if(sm[i]>sn[i]) res=0;
        else if(sm[i]==sn[i]) res=res*(!g[i]+1)%mod;
        else res=res*sn[i]%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
