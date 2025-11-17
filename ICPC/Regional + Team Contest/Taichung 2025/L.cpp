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
#define ld long double
const int N = 3005;
int dp[N][N][2];

void solve(){
    int n,m,k;cin >> n >> m >> k;
    vector<int> c(n+1);

    string s;cin >> s;
    for(int i=1;i<n;i++) c[i]=(s[i]!=s[i-1]);

    vector<int> f(m+1,-inf);f[0]=0;
    for(int d=0;d<k;d++){
        //i*k+d 
        vector<int> a;
        for(int i=0;i*k+d<=n;i++) a.push_back(c[i*k+d]);
        int sz=(int)a.size();
        

        for(int i=0;i<sz;i++) for(int j=0;j<sz;j++) dp[i][j][0]=dp[i][j][1]=-inf;

        dp[0][0][a[0]]=0;
        for(int i=0;i+1<sz;i++) for(int j=0;j<=i;j++){
            for(int x=0;x<=1;x++){
                if(dp[i][j][x]==-inf) continue;
                //cout << "dp " << i << ' ' << j << ' ' << x << '\n';
                //cout << "nxt " << i+1 << ' ' << j << ' ' << a[i+1] << '\n';
                dp[i+1][j][a[i+1]]=max(dp[i+1][j][a[i+1]],dp[i][j][x]+x*((i*k+d)>0));
                dp[i+1][j+1][a[i+1]^1]=max(dp[i+1][j+1][a[i+1]^1],dp[i][j][x]+(x^1)*((i*k+d)>0));
            }
        }

        vector<int> val(sz,-inf);
        for(int j=0;j<sz;j++) for(int x=0;x<=1;x++){
            //cout << '*' << j << ' ' << dp[sz-1][j][x] << '\n';
            val[j]=max(val[j],dp[sz-1][j][x]+x*(((sz-1)*k+d)<n));
        }
        for(int i=m;i>=0;i--){
            if(f[i]==-inf) continue;
            for(int j=min(m-i,sz-1);j>=0;j--) f[i+j]=max(f[i+j],f[i]+val[j]);
        }
    }
    int res=-inf;
    for(int i=0;i<=m;i++) res=max(res,f[i]);
    cout << res+1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
