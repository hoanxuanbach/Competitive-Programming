#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    vector<int> fac(n+1),dfac(n+1);
    fac[0]=dfac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    auto C = [&](int N,int K){
        if(N<K || N<0 || K<0) return 0LL;
        return fac[N]*dfac[K]%mod*dfac[N-K]%mod;
    };

    int res=0,inv2=(mod+1)/2;
    for(int x=1;x<n;x++){
        int val=power(x,x-1)*power(n-x,n-x-1)%mod;
        val=val*C(n,x)%mod;
        res=(res+val*min(x,n-x))%mod;
    }
    res=res*inv2%mod;

    res=res*fac[n-1]%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
