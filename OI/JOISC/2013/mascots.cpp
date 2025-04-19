#include<bits/stdc++.h>
using namespace std;
#define maxn 3005
#define int long long
const int mod=1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=(a*a)%mod;n>>=1;
    }
    return res;
}
int f(int n){
    int res=1;
    for(int i=2;i<=n;i++) res=(res*i)%mod;
    return res;
}
int fac[maxn],dfac[maxn];
int C(int k,int n){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int x,y,u,v,n,m,q,dp[maxn][maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q;fac[0]=dfac[0]=1;
    for(int i=1;i<=max(n,m);i++){
        fac[i]=fac[i-1]*i%mod;
        dfac[i]=dfac[i-1]*power(i,mod-2)%mod;
    }
    x=n;y=m;
    for(int i=1;i<=q;i++){
        int a,b;cin >> a >> b;
        x=min(x,a);y=min(y,b);
        u=max(u,a);v=max(v,b);
    }
    int r=x-1+n-u,c=y-1+m-v,num=(u-x+1)*(v-y+1)-q;
    int ans=f(num)*C(n-u,r)%mod*C(m-v,c)%mod;
    for(int i=0;i<=r;i++){
        for(int j=0;j<=c;j++){
            if(i==0 && j==0){dp[i][j]=1;continue;}
            if(i>=1) dp[i][j]=(dp[i][j]+dp[i-1][j]*fac[v-y+j+1])%mod;
            if(j>=1) dp[i][j]=(dp[i][j]+dp[i][j-1]*fac[u-x+i+1])%mod;
        }
    }
    ans=ans*dp[r][c]%mod;
    cout << ans << '\n';
}
