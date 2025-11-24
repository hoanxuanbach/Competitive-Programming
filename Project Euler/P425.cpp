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
    int N;cin >> N;
    vector<int> p(N);p[0]=p[1]=1;
    vector<int> f(N),X;
    for(int i=2;i<N;i++) if(!p[i]){
        f[i]=(int)X.size();
        X.push_back(i);
        for(int j=i*2;j<N;j+=i) p[j]=1;
    }
    int n=(int)X.size();
    vector<vector<int>> g(n);
    for(int a:X){
        int d=1,x=a;
        while(x){
            int k=x%10;x/=10;
            for(int i=k+1;i<10;i++){
                int b=a-k*d+i*d;
                if(b<N && !p[b]) g[f[b]].push_back(f[a]);
            }
            d*=10;
        }
        for(int i=1;i<10;i++){
            int b=a+i*d;
            if(b<N && !p[b]) g[f[b]].push_back(f[a]);
        }
    }
    
    vector<int> par(n);
    iota(par.begin(),par.end(),0);

    function<int(int)> fp = [&](int u){
        if(u!=par[u]) return par[u]=fp(par[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        u=fp(u);v=fp(v);
        if(u==v) return;
        par[v]=u;
    };

    int res=0;
    for(int i=0;i<n;i++){
        for(int x:g[i]) unite(x,i);
        if(fp(i)!=fp(0)){
            //cout << X[i] << '\n';
            res+=X[i];
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
