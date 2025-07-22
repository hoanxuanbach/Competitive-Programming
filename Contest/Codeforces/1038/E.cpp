#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int mod = 998244353;
const int maxn = 2e5+5;

void solve(){   
    int n,k;cin >> n >> k;
    vector<int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    int mul=1;
    if(a[1]==-1) a[1]=1,mul*=k;
    if(b[n]==-1) b[n]=1,mul*=k;

    vector<vector<int>> dp(n+1,vector<int>(k+1,0));

    auto f = [&](int x,int y,int d){
        if(x==-1 && y==-1) return k-d;
        else if(x==-1) return (int)((y+d)<=k);
        else if(y==-1) return (int)((x-d)>=1);
        else return (int)((x-y)==d);
    };

    dp[1][k]=1;
    for(int i=1;i<n;i++) for(int j=0;j<=k;j++){
        //a[i+1]>=b[i]
        for(int x=0;x<=j;x++){
            int nj=(j==k?k:j-x);
            dp[i+1][nj]=(dp[i+1][nj]+dp[i][j]*f(a[i+1],b[i],x))%mod;
        }

        //a[i+1]<b[i];
        for(int x=1;x<k;x++) dp[i+1][x]=(dp[i+1][x]+dp[i][j]*f(b[i],a[i+1],x))%mod;
    }

    int total=0;
    for(int i=0;i<=k;i++) total=(total+dp[n][i])%mod;
    cout << total*mul%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}