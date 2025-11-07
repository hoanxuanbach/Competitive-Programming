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
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    int x=-1,y=-1;
    auto f = [&](int u,int v){
        int k=v%u;
        if(!(k&1)) x=u,y=v;
    };
    if(n<=100){
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) f(a[i],a[j]);
    }
    else{
        vector<int> X,Y;
        for(int i=0;i<n;i++){
            if(a[i]&1) X.push_back(a[i]);
            else Y.push_back(a[i]);
        }
        for(int i=1;i<(int)X.size();i++) f(X[i-1],X[i]);
        for(int i=1;i<(int)Y.size();i++) f(Y[i-1],Y[i]);
    }
    if(x==-1) cout << -1 << '\n';
    else cout << x << ' ' << y << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
