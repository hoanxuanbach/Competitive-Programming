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
 
const int maxn = 1e7+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn];
void init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int m,n;cin >> m >> n;
    init(m);

    int res=0;
    for(int x=1;x<=m;x++){
        int k=(x&1?1:-1);
        int val=0;
        if(x==m) val=1;
        else if(x==m-1) val=(n+1)%mod;
        else val=(power(m-x,n+1)+mod-1)*power(m-x-1,mod-2)%mod;
        (res+=k*C(m,x)*val%mod+mod)%=mod;
    }
    cout << res << '\n';    
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
