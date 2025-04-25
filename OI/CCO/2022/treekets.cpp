#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 4005;
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int fac[maxn],dfac[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(k>n || n<0 || k<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

bool check=true;
int n,k,cnt[maxn],s[maxn];
int dp[maxn][maxn],L[maxn],R[maxn];

void dfs(int u,int d){
    s[u]=1-cnt[u];
    if(L[u]) dfs(L[u],0),s[u]+=s[L[u]];
    if(R[u]) dfs(R[u],1),s[u]+=s[R[u]];
    if(s[u]<0){
        check=false,s[u]=0;
        return;
    }
    int x=L[u],y=R[u];
    if(d) swap(x,y);
    for(int i=0;i<=s[x];i++) for(int j=0;j<=s[y];j++){
        int k=i+j-cnt[u];
        if(k<0) continue;
        int val=0;
        if(i==s[x]) val=C(i+j,i);
        else if(cnt[u]>=j) val=C(cnt[u],j);
        dp[u][k]=(dp[u][k]+val*dp[x][i]%mod*dp[y][j])%mod;
    }
    {
        int k=s[x]+s[y]+1-cnt[u];
        if(k>=0){
            int val=fac[s[x]+s[y]+1]*dfac[s[x]]%mod*dfac[s[y]]%mod;
            dp[u][k]=(dp[u][k]+val*dp[x][s[x]]%mod*dp[y][s[y]])%mod;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;combi(n);
    for(int i=1;i<=k;i++){int x;cin >> x;cnt[x]++;}
    for(int i=1;i<=n;i++) cin >> L[i] >> R[i];
    dp[0][0]=1;dfs(1,0);
    cout << (check?dp[1][0]:0) << '\n';
}
