#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int mod = 998244353;
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
    if(n<k || n<0 || k<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int n;cin >> n >> mod;combi(2*n);
    vector<int> ans(n+1);
    for(int i=1;i<=n;i++) for(int x=0;x<=i;x++) ans[i]=(ans[i]+fac[i]*x%mod)%mod;

    vector<vector<int>> f(n+1,vector<int>(n+1,0));
    for(int i=0;i<=n;i++) for(int j=i;j<n-i;j++) f[i][j+1]=(C(i+j,j)-C(i+j,j+1)+mod)%mod;
    for(int i=0;i<=n;i++) for(int j=0;j<=n-i;j++){
        f[i][j]=f[i][j]*fac[i]%mod*fac[j]%mod;
        if(j) f[i][j]=(f[i][j]+f[i][j-1]*j)%mod;
        if(i) f[i][j]=(f[i][j]+f[i-1][j]*i)%mod;
        ans[i+j]=(ans[i+j]-f[i][j]+mod)%mod;
    }
    for(int i=1;i<=n;i++) cout << ans[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
