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
 
const int maxn = 1e2+5;
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
    if(n<k || n<0 || k<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

int p[maxn];
int dp[maxn][maxn][maxn];
void solve(){
    int n;cin >> n;init(n);

    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    
    vector<int> f(n+1,1);
    for(int i=0;i<n;i++){
        int x;cin >> x;
        p[a[i]]=x;f[x]=0;
    }

    f[0]=0;
    vector<int> X={0};
    for(int i=1;i<=n;i++){
        if(f[i]) X.push_back(i);
        f[i]+=f[i-1];
    }

    int d=0;
    dp[0][0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++) for(int k=0;k<=min(f[j],d);k++){
            if(!dp[i][j][k]) continue;
            if(p[i+1]){
                int nj=max(j,p[i+1]);
                if(p[i+1]>j) (dp[i+1][j][k]+=dp[i][j][k])%=mod;

                int s=f[nj]-f[j];
                for(int x=0;x<=min(d-k,s);x++){
                    (dp[i+1][nj][k+x]+=dp[i][j][k]*fac[d-k]%mod*dfac[d-k-x]%mod*C(s,x))%=mod;
                }
            }
            else{
                (dp[i+1][j][k]+=dp[i][j][k])%=mod;
                (dp[i+1][j][k+1]+=dp[i][j][k]*(f[j]-k))%=mod;
                for(int t=f[j]+1;t<=f[n];t++){
                    int nj=X[t],s=t-f[j]-1;
                    for(int x=0;x<=min(d-k,s);x++){
                        (dp[i+1][nj][k+x+1]+=dp[i][j][k]*fac[d-k]%mod*dfac[d-k-x]%mod*C(s,x))%=mod;
                    }
                }
            }
        }
        d+=!p[i+1];
    }
    int res=0;
    for(int i=0;i<=n;i++) res=(res+dp[n][i][f[i]]*fac[d-f[i]])%mod;
    cout << res << '\n';
}   
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
