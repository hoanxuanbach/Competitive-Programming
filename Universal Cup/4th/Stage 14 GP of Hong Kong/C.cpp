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
 
const int maxn = 1e7+5;
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
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod,inv[i]=dfac[i]*fac[i-1]%mod;
}
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
/*

a_i >= b_i 
S-T+max(b_i) < n
*/
void solve(){
    int n;cin >> n;
    vector<int> a(n);
    combi(n*n);
    
    int S=0;
    for(int i=0;i<n;i++) cin >> a[i],S+=a[i];
    sort(a.begin(),a.end());

    int res=1;
    for(int x=1;x<=n;x++) res=(S+x)%mod*res%mod*inv[x]%mod;

    vector<int> dp(n);dp[0]=1;

    int pos=0,sum=0;
    for(int k=n-1;k>=0;k--){
        int T=S-k,m=n-k;
        if(T>(m-1)*n || T<0) continue;
        while(pos<n && a[pos]<m){
            for(int i=1;i<n;i++) dp[i]=(dp[i]+dp[i-1])%mod;
            for(int i=n-1;i>=a[pos]+1;i--) dp[i]=(dp[i]-dp[i-a[pos]-1]+mod)%mod;
            sum+=a[pos++];
        }
        int s=n-pos;
        if(!s) res=(res+dp[k])%mod;
        else{
            for(int x=0;x<=k;x++){
                int d=k-x-(S-sum-(m-1)*s),cnt=0;
                if(d<0) continue;
                for(int i=0;i<=d/m;i++){
                    int X=d-i*m;
                    int val=(C(s,i)*C(X+s-1,s-1))%mod;
                    if(i&1) cnt=(cnt+mod-val)%mod;
                    else cnt=(cnt+val)%mod;
                }
                res=(res+cnt*dp[x])%mod;
            }
        }

        for(int x=0;x<=min(n,T/m);x++){
            int X=T-m*x;
            int val=C(n,x)*C(X+n-1,n-1)%mod;
            if(x&1) res=(res+val)%mod;
            else res=(res-val+mod)%mod;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}