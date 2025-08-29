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
    vector<int> a(n+1),dp(n+1);
    vector<vector<int>> p(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        dp[i]=dp[i-1];
        p[a[i]].push_back(i);
        if((int)p[a[i]].size()>=a[i]){
            int x=p[a[i]].end()[-a[i]]-1;
            dp[i]=max(dp[i],dp[x]+a[i]);
        }
    }
    cout << dp[n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
