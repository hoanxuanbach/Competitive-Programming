#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2=(mod+1)/2;
const int maxn = 2e3+5;
const int maxa = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(1);
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
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

void init(){

}

void solve(){
    int n,m;cin >> n >> m;

    auto f = [&](int p){
        return (m*inv2+(1-power((1-2*p)%mod,m))*power(4*p%mod,mod-2))%mod;
    };

    int T=0;
    vector<int> p(n);
    for(int i=0;i<n;i++) cin >> p[i],T=(T+p[i])%mod;
    for(int i=0;i<n;i++) p[i]=p[i]*power(T,mod-2)%mod;
    int res=0;
    for(int i=0;i<n;i++) res=(res+f(p[i])*p[i])%mod;
    cout << (res%mod+mod)%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}