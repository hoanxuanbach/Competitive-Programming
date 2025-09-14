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
    auto c = [&](int x){
        return x*(x-1)/2;
    };

    int total=0;
    map<pii,int> mp;
    vector<pii> P(n);
    for(int i=0;i<n;i++) mp[P[i]={i,n+i}]++;

    vector<int> f(2*n);
    vector<set<int>> g(2*n);
    iota(f.begin(),f.end(),0);
    for(int i=0;i<2*n;i++) g[i].insert(i%n);

    auto update = [&](int x,int v,int u){
        if(P[x].first==P[x].second) return;
        int sz=mp[P[x]];mp[P[x]]--;
        total=total+c(sz)-c(sz-1);
        if(P[x].first==v) P[x].first=u;
        if(P[x].second==v) P[x].second=u;
        if(P[x].first>P[x].second) swap(P[x].first,P[x].second);
        if(P[x].first==P[x].second) return;
        sz=mp[P[x]];mp[P[x]]++;
        total=total+c(sz)-c(sz+1);
    };
    function<int(int)> ff = [&](int u){
        if(u!=f[u]) return f[u]=ff(f[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        u=ff(u);v=ff(v);
        if(u==v) return;
        if((int)g[u].size()<(int)g[v].size()) swap(u,v);
        total-=c((int)g[u].size())+c((int)g[v].size());
        f[v]=u;
        for(int x:g[v]){
            g[u].insert(x);
            update(x,v,u);
        }
        total+=c((int)g[u].size());
    };

    for(int i=1;i<=m;i++){
        int a,b;cin >> a >> b;
        a--;b--;unite(a,n+b);
        cout << total << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
