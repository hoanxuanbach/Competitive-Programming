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
    int n,k=60;cin >> n;
    vector<int> a(n+1),f(n+1),g(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];g[i]=1;
        if(i>=k) g[i]=max(g[i],f[i-k]+1);
        for(int j=1;j<min(i,k);j++){
            int d=__builtin_popcountll(a[i]^a[i-j]);
            if(j>=d) g[i]=max(g[i],g[i-j]+1);
        }
        f[i]=max(f[i-1],g[i]);
    }
    cout << n-f[n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
