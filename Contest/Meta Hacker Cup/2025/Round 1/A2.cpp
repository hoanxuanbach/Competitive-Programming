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
    vector<int> a(n+1);
    
    vector<array<int,3>> e;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        e.push_back({a[i],0,i});
        if(i>1) e.push_back({abs(a[i-1]-a[i]),i-1,i});
    }
    sort(e.begin(),e.end());

    int res=0;
    vector<int> f(n+1);
    iota(f.begin(),f.end(),0);

    function<int(int)> get_f = [&](int u){
        if(u!=f[u]) return f[u]=get_f(f[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        u=get_f(u);v=get_f(v);
        if(u==v) return false;
        f[v]=u;return true;
    };
    for(auto [w,u,v]:e){
        if(unite(u,v)) res=w;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
