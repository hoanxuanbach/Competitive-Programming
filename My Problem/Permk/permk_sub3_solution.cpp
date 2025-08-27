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

const int root = 3;
const int iroot = power(3,mod-2);
const int maxn = 2e5+5;

int fac[maxn],f[maxn],g[maxn];
void solve(){
    int n,k;cin >> n >> k;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%mod;
        f[i]=fac[i];
        g[i]=0;
    }
    g[k]=f[k];

    for(int i=1;i<=k;i++) for(int j=1;j<i;j++) f[i]=(f[i]-f[j]*fac[i-j]%mod+mod)%mod;
    for(int i=k+1;i<=n;i++) for(int j=1;j<=k;j++) g[i]=(g[i]+g[i-j]*f[j])%mod;
    
    cout << g[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}