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
    vector<int> p(N),sz(N,1);
    iota(p.begin(),p.end(),0);

    vector<int> S(N+1);
    for(int i=1;i<=55;i++) S[i]=(100003 - 200003*i%N + 300007*i%N*i%N*i+N)%N;
    for(int i=56;i<=N;i++) S[i]=(S[i-24]+S[i-55])%N;

    function<int(int)> fp = [&](int u){
        if(u!=p[u]) return p[u]=fp(p[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        u=fp(u),v=fp(v);
        if(u!=v){
            p[v]=u;
            sz[u]+=sz[v];
        }
    };

    int n=0,root=524287,k=0;
    while(sz[fp(root)]<99*N/100){
        n++;
        if(2*n-1>=(int)S.size()){
            S.push_back(0);
            S.push_back(0);
            S[2*n-1]=(S[2*n-25]+S[2*n-56])%N;
            S[2*n]=(S[2*n-24]+S[2*n-55])%N;
        }
        int u=S[2*n-1],v=S[2*n];
        if(u==v) k++;
        unite(u,v);
    }
    cout << n-k << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
