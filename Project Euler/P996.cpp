#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1234567891;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int maxn = 1e7+5;
int fac[maxn],dfac[maxn]; 
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(n<0 || k<0 || n<k) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int F(int n,int k){
    return (C(2*k-1,n-1)-n*C(k-1,n-1)%mod+mod)%mod;
}

int suf[maxn];
int cal(vector<int> f,int n,int k){
    if(k<=n) return f[k];
    suf[n+1]=1;
    for(int i=n;i>=1;i--) suf[i]=(suf[i+1]*(k-i))%mod;
    int ans=0,pre=1;
    for(int i=1;i<=n;i++){
        int mul=(f[i]*pre%mod)*suf[i+1]%mod;
        mul=(mul*dfac[i-1]%mod)*dfac[n-i]%mod;
        if((n-i)&1) mul=(mod-mul)%mod;
        ans=(ans+mul)%mod;
        pre=(pre*(k-i))%mod;
    }
    return ans;
};

const int S = 1005;
int dp[S][S];
void solve(){
    int n,M;cin >> n >> M;M/=2;
    int m=min(M,2*n);combi(2*M);

    dp[0][0] = 1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=(dp[i-1][j]+F(i,j))%mod;
            for(int d=1;d<i;d++) for(int k=1;k<=j;k++) (dp[i][j]+=F(d,k)*dp[i-d-1][j-k])%=mod;
        }
    }

    vector<int> f(m+1);f[0]=dp[n][0];
    for(int i=1;i<=m;i++){
        f[i]=(dp[n][i]+f[i-1])%mod;
    }

    cout << cal(f,m,M) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
