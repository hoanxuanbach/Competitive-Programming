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
 
const int maxn = 6e3+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int n,a[maxn],s[maxn],dp[maxn][maxn],f[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],s[i]=s[i-1]+a[i],f[i]=inf;
    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) dp[i][j]=inf;

    int mx=0;
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        f[x]=min(f[x],i);
        mx=max(mx,x);
    }
    if(!mx){
        cout << 0 << '\n';
        return;
    }
    for(int i=n;i>=1;i--) f[i-1]=min(f[i-1],f[i]);
    f[0]=inf;

    for(int i=0;i<=n;i++) dp[0][i]=0;
    for(int i=0;i<n;i++){
        int val=inf;
        for(int j=0;j<=n-i;j++){
            if(i+j>f[j]) val=inf;
            val=min(val,dp[i][j]);
            dp[i+j][j]=min(dp[i+j][j],val+s[i+j]-s[i]);
        }
        for(int j=0;j<=i;j++) dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
    }
    int res=inf;
    for(int i=1;i<=f[mx];i++) res=min(res,dp[i][mx]);
    cout << res << '\n';
}
 
signed main(){
    freopen("A.txt","r",stdin);
    freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
