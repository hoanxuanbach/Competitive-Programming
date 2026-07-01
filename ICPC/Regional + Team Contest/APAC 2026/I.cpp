#include <bits/stdc++.h>

using namespace std;

#define int long long 
const int N = 5e5+5;
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[N],dfac[N],inv[N];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

const int L = 20;

int dp[N][L+5][2];

void solve() {
    int n;cin >> n;

    int M=0;
    combi(2*n+L);
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i],M=max(M,a[i]);

    vector<int> cnt(M+1);
    for(int i=n-1;i>=1;i--) a[i]=min(a[i],a[i+1]),cnt[a[i]]++;
    cnt[a[n]]++;

    for(int i=M-1;i>=1;i--) cnt[i]+=cnt[i+1];
    //for(int i=1;i<=M;i++) cout << cnt[i] << ' ';
    //cout << '\n';

    int res=0;
    for(int i=M;i>=1;i--){
        int T=min(cnt[i],n-1),A=1,B=0;
        for(int j=1;j<L;j++) dp[i][j-1][0]=C(T+j-1,T-1);
        for(int x=i*2;x<=M;x+=i){
            A=(A+dp[x][0][0])%mod;
            B=(B+dp[x][0][1])%mod;
            for(int k=1;k<L;k++) for(int t=0;t<=1;t++) dp[i][k-1][t^1]=(dp[i][k-1][t^1]+dp[x][k][t])%mod;
            for(int j=1;j<L;j++) for(int t=0;t<=1;t++) dp[i][j-1][t]=(dp[i][j-1][t]+dp[x][0][t]*C(T+j-1,T-1))%mod;
        }
        //cout << i << ' ' << dp[i][0][0] << ' ' << dp[i][0][1] << '\n';
        if(cnt[i]==n){
            //cout << "* " << i << ' ' << A << ' ' << B << '\n';
            res=(res+A-B+mod)%mod;
        }
    }
    cout << res << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_test = 1;
    // cin >> num_test;
    while (num_test--) {
        solve();
    }
}