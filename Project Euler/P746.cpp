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

int fac[maxn],dfac[maxn],pw[maxn];
int C(int n,int k){
    if(n<0 || k<0 || n<k) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void init(int n){
    n*=4;fac[0]=pw[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,pw[i]=pw[i-1]*4%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}

int cal(int n){
    int res=fac[2*n]*fac[2*n]%mod;
    for(int i=1;i<=n;i++){
        int d=4*n-4*i,mul=pw[i]*fac[d/2]%mod*fac[d/2]%mod*C(n,i)%mod*fac[i]%mod;
        int cnt=(C(d+i,i)+3*C(d+i-1,i-1))%mod;
        if(i==1 && n==1) cnt=1;
        cnt=cnt*mul%mod;
        if(i&1) res=(res+mod-cnt)%mod;
        else res=(res+cnt)%mod;
    }
    return res*2%mod;
}

void solve(){
    int n;cin >> n;init(n);
    int res=0;
    for(int i=1;i<=n;i++) res=(res+cal(i))%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
