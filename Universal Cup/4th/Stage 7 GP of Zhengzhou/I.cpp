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

int fac[maxn],dfac[maxn];
int C(int n,int k){
    if(n<k || n<0 || k<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;  
}

void solve(){
    int n,k;cin >> n >> k;

    int m=max(n,k);
    fac[0]=dfac[0]=1;
    for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%mod;
    dfac[m]=power(fac[m],mod-2);
    for(int i=m;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    vector<int> f(n,1);
    int res=0;
    for(int x=1;x<=k;x++){
        int mul=C(k,x)*power(dfac[n],x)%mod;
        if(!(x&1)) mul=(mod-mul)%mod;
        for(int i=1;i<n;i++){
            f[i]=f[i]*i%mod;
            mul=mul*(f[i]+1)%mod;
        }
        res=(res+mul)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
