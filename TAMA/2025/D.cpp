#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int inv2=(mod+1)/2;
const int inv3=(mod+1)/3;

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){   
    int N;cin >> N;
    auto f3 = [&](int x){
        x=(x*(x+1)/2)%mod;
        return x*x%mod;
    };
    auto f2 = [&](int x){
        return (x*(x+1)/2)%mod*(2*x+1)%mod*inv3%mod;
    };
    auto f = [&](int x){
        return (x*(x+1)/2)%mod;
    };
    int res=0,S=sqrtl(N);
    for(int r=1;r<=S;r++){
        int X=(N/r)%mod;
        int val=f(r)*f(X)%mod;
        res=(res+mod-val)%mod;
        val=r*f2(X)%mod*(X+1)%mod;
        res=(res+val)%mod;
        val=r*f3(X)%mod;
        res=(res+mod-val)%mod;
        val=r*r%mod*f(X)%mod*(X+1)%mod;
        res=(res+val)%mod;
        val=r*r%mod*f2(X)%mod;
        res=(res+mod-val)%mod;
    }
    auto g = [&](int x){
        return (f2(x)+f(x))*inv2%mod;
    };
    for(int c=1;c<S;c++){
        int r=N/c,l=N/(c+1);
        l%=mod;r%=mod;
        int val=(g(r)-g(l)+mod)%mod*f(c)%mod;
        res=(res+mod-val)%mod;
        val=c*c%mod*c%mod*(f(r)-f(S)+mod)%mod;
        res=(res+mod-val)%mod;
        val=c*c%mod*(f2(r)-f2(S)+mod)%mod;
        res=(res+mod-val)%mod;

        val=f(c)*(f2(r)-f2(l)+mod)%mod*(c+1)%mod;
        res=(res+val)%mod;
        val=f2(c)*(f(r)-f(l)+mod)%mod*(c+1)%mod;
        res=(res+val)%mod;
    }


    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}