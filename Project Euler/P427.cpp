#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+9;
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
    vector<int> f(n+1),g(n+1);
    f[0]=g[0]=1;
    for(int i=1;i<=n;i++) f[i]=f[i-1]*n%mod,g[i]=g[i-1]*(n-1)%mod;

    vector<int> fac(n+1),dfac(n+1);
    fac[0]=dfac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    auto C = [&](int N,int K){
        if(N<K || K<0 || N<0) return 0LL;
        return fac[N]*dfac[K]%mod*dfac[N-K]%mod;
    };

    int cur=0,res=0;
    for(int k=1;k<=n;k++){
        int val=f[n];
        for(int j=1;k*j<=n;j++){
            int m=n-k*j;
            
            int cnt=0;
            if(j<=m){
                cnt=(cnt+C(m-1,j-1)*g[j-1]%mod*f[m-j+1])%mod;
                cnt=(cnt+C(m-1,j)*g[j]%mod*f[m-j])%mod;
            }
            val=(val+(j&1?-cnt:cnt)+mod)%mod;
        }
        //cout << k << ' ' << val << '\n';
        res=(res+(val-cur+mod)*k)%mod;
        cur=val;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
