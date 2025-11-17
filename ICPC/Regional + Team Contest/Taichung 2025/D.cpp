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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];

    vector<bool> jmp(n);
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) if(a[j]%a[i]==0 && b[j]) jmp[i]=true;
    
    vector<int> fac(n+1),dfac(n+1),inv(n+1);
    fac[0]=dfac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod,inv[i]=dfac[i]*fac[i-1]%mod;

    vector<int> res(m+1);
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        dp[i][0]++;
        if(!b[i]){
            int k=1;
            for(int x=i+1;x<n;x++){
                if(a[x]%a[i]!=0) continue;
                if(!b[x] && !jmp[x]) continue;
                for(int j=0;j<=i;j++) dp[x][j+k]=(dp[x][j+k]+dp[i][j]*inv[j+k])%mod;
                k++;
                if(b[x]) break;
            }
        }
        else{
            for(int j=0;j<=i;j++) res[b[i]]=(res[b[i]]+dp[i][j])%mod;
        }
    }
    for(int i=1;i<=m;i++) cout << res[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
