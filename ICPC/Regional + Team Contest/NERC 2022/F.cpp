#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 5005
const int mod=998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=(a*a)%mod;n>>=1;
    }
    return res;
}
int a[maxn],cnt[maxn],dp[maxn][maxn],suf[maxn],fac[maxn],dfac[maxn];
int C(int k,int n){
    if(k>n || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void solve(){
    int n;cin >> n;vector<int> x;
    for(int i=1;i<=n;i++){cin >> a[i];x.push_back(a[i]);}
    sort(x.begin(),x.end());
    x.erase(unique(x.begin(),x.end()),x.end());
    int m=(int)x.size();n/=2;suf[m+1]=0;
    for(int i=1;i<=m;i++) cnt[i]=0;
    for(int i=1;i<=2*n;i++) cnt[lower_bound(x.begin(),x.end(),a[i])-x.begin()+1]++;
    for(int i=m;i>=1;i--) suf[i]=suf[i+1]+cnt[i];
    if(cnt[m]>1){
        cout << 0 << '\n';
        return;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) dp[i][j]=0;
    }
    dp[n][m]=1;
    for(int i=n;i>=2;i--){
        for(int j=m;j>=2;j--){
            int num=2*n-2*i+1-suf[j];
            dp[i][j-1]=(dp[i][j-1]+C(cnt[j-1],num)*dp[i][j])%mod;
            dp[i-1][j-1]=(dp[i-1][j-1]+C(cnt[j-1]-1,num)*dp[i][j])%mod;
        }
    }
    int ans=0,mul=1,d=fac[cnt[1]];
    for(int i=2;i<=m;i++){
        ans=(ans+dp[1][i]*mul)%mod;
        d=(d*fac[cnt[i]])%mod;
        mul=fac[suf[1]-suf[i+1]]*power(d,mod-2)%mod;
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    fac[0]=dfac[0]=1;
    for(int i=1;i<=5000;i++){
        fac[i]=fac[i-1]*i%mod;
        dfac[i]=dfac[i-1]*power(i,mod-2)%mod;
    }
    int t;cin >> t;
    while(t--) solve();
}
