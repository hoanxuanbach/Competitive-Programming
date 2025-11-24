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

int dp[65][125][125][2];

void solve(){
    int n;cin >> n;
    dp[0][n][n][0]=1;
    for(int i=0;i<n;i++) for(int j=n-i;j<=n+i;j++) for(int k=n-i;k<=n+i;k++){
        for(int t=0;t<=1;t++){
            for(int d:{-1,1}){
                int nj=j+d,nk=k,nt=t;
                if(i) nk=max(nk,j);
                if(j>=n && i) nt=1;
                dp[i+1][nj][nk][nt]+=dp[i][j][k][t];
            }
        }
    }
    int res=0;
    for(int i=0;i<=2*n;i++) for(int j=0;j<=2*n;j++){
        if(j-i<0) continue;
        res+=dp[n][i][j][1];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
