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
    int A,B;cin >> A >> B;
    vector<int> d(A),f(A);

    for(int i=0;i<A;i++) f[i]=i*B%A,d[i]=((i+1)*B%A>i*B%A?(B/A):(B/A)+1);
    vector<vector<int>> dp(A,vector<int>(B)),cnt(A,vector<int>(B));
    cnt[0][0]=1;
    for(int i=0;i+1<A;i++) for(int j=0;j<B;j++) if(cnt[i][j]){
        
        cnt[i+1][j+d[i]]+=cnt[i][j];
        dp[i+1][j+d[i]]+=dp[i][j];

        for(int k=0;k<(j+d[i]);k++){
            cnt[i+1][k]+=cnt[i][j];
            dp[i+1][k]+=dp[i][j]+cnt[i][j]*(k*A+f[i+1]);
        }
    }

    int res=0;
    for(int i=0;i<B;i++) res+=dp[A-1][i];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
