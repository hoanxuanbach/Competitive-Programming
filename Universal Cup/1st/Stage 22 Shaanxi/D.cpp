#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

void solve(){
    int n;cin >> n;
    vector<int> fac(n+1,1),dfac(n+1,1);
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    int res=0;
    for(int x=1;(2*x-1)<=n;x++) res=(res+fac[n-x]*fac[n-x]%mod*dfac[n-2*x+1]%mod)%mod;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}