#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1020202009;
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
    
    vector<int> fac(n+1,1),dfac(n+1,1);
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    auto C = [&](int N,int K){
        if(N<0 || K<0 || N<K) return 0LL;
        return fac[N]*dfac[N-K]%mod*dfac[K]%mod;
    };

    vector<array<int,2>> f(n+1);
    f[0]={1,0};

    for(int i=1;i<=n;i++){
        f[i]={0,0};
        for(int k=0;k<=1;k++){
            for(int j=1;j<=i;j++) f[i][k]=(f[i][k]+f[j-1][0]*f[i-j][k^1]%mod*C(i-1,j-1)%mod)%mod;
        }
    }
    cout << (f[n][0]+f[n][1])%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
