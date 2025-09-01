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
 
const int maxn = 5e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int P(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod;
}
void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int g[maxn],p[maxn];

void solve(){
    int n,m,l,k;cin >> n >> m >> l >> k;
    int S=min({n,m,l}),X=1;
    for(int i=1;i<=S;i++){
        p[i]=(n*m%mod*l%mod-(n-i)*(m-i)%mod*(l-i)%mod+mod)%mod;
        X=X*p[i]%mod;
    }
    g[S]=power(X,mod-2);
    for(int i=S;i>=1;i--) g[i-1]=g[i]*p[i]%mod;
    int ans=0;
    for(int i=k;i<=S;i++){
        int val=g[i]*P(n,i)%mod*P(m,i)%mod*P(l,i)%mod*C(i,k)%mod;
        if((i-k)&1) ans=(ans+mod-val)%mod;
        else ans=(ans+val)%mod;
    }
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    combi(5000000);
    int test=1;cin >> test;
    while(test--) solve();
}
