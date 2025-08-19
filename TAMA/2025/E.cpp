#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
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
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}


void solve(){   
    int n,k;cin >> n >> k;combi(n);

    vector<int> g(n+1);
    g[1]=1;
    for(int i=2;i<=n;i++){
        g[i]=power(2,i*(i-1)/2);
        for(int j=1;j<i;j++) g[i]=(g[i]-g[j]*C(i-1,j-1)%mod*power(2,(i-j)*(i-j-1)/2)%mod+mod)%mod;
        //cout << g[i] << ' '; 
    }
    //cout << '\n';

    vector<int> h(n+1);
    vector<vector<int>> f(n+1,vector<int>(n+1,0));
    f[1][1]=1;h[1]=1;
    for(int i=2;i<=n;i++){
        h[i]=g[i];
        for(int k=2;k<=i;k++){
            for(int j=1;j<i;j++) f[i][k]=(f[i][k]+f[j][1]*C(i-1,j-1)%mod*f[i-j][k-1]%mod)%mod;
            h[i]=(h[i]-f[i][k]*power(i,k-2)%mod+mod)%mod;
        }
        f[i][1]=h[i]*i%mod;
        //cout << h[i] << ' ';
    }
    //cout << '\n';
    for(int i=1;i<=n;i++) for(int j=1;j<=i;j++){
        if(j>=2) f[i][j]=f[i][j]*power(i,j-2)%mod;
        else f[i][j]=h[i];
    }

    vector<vector<int>> dp(n+1,vector<int>(k+1,0));
    dp[0][0]=1;
    for(int i=1;i<=n;i++) for(int j=1;j<=min(i,k);j++){
        for(int x=1;x<=i;x++) for(int y=1;y<=min(x,j);y++) dp[i][j]=(dp[i][j]+C(i-1,x-1)*dp[i-x][j-y]%mod*f[x][y]%mod)%mod;
    }
    cout << dp[n][k] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}