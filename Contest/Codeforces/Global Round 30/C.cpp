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
    vector<int> a(n),b(m),c(m);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> b[i];
    vector<pii> P;
    vector<int> X;
    for(int i=0;i<m;i++){
        cin >> c[i];
        if(!c[i]) X.push_back(b[i]);
        else P.push_back({b[i],c[i]});
    }
    sort(P.begin(),P.end());
    sort(X.begin(),X.end());
    
    set<pii> S;
    for(int i=0;i<n;i++) S.insert({a[i],i});

    int res=0;
    for(auto [d,x]:P){
        auto it=S.lower_bound({d,-1});
        if(it==S.end()) continue;
        auto [cx,id]=*it;S.erase(it);
        res++;
        cx=max(cx,x);
        S.insert({cx,id});
    }

    for(int x:X){
        auto it=S.lower_bound({x,-1});
        if(it==S.end()) continue;
        res++;
        S.erase(it);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
