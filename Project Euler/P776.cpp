#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
__int128 dp[25][200][2],cnt[25][200][2];

void solve(){
    string S;cin >> S;
    int n=(int)S.length();

    dp[0][0][0]=0;cnt[0][0][0]=1;
    for(int i=0;i<n;i++) for(int x=0;x<=9*i;x++){
        int c=S[i]-'0';
        for(int d=0;d<=9;d++){
            if(d<c) dp[i+1][x+d][1]+=dp[i][x][0]*10+cnt[i][x][0]*d,cnt[i+1][x+d][1]+=cnt[i][x][0];
            else if(d==c) dp[i+1][x+d][0]+=dp[i][x][0]*10+cnt[i][x][0]*d,cnt[i+1][x+d][0]+=cnt[i][x][0];
            dp[i+1][x+d][1]+=dp[i][x][1]*10+cnt[i][x][1]*d,cnt[i+1][x+d][1]+=cnt[i][x][1];
        }
    }

    ld res=0;
    for(int x=1;x<=9*n;x++){
        __int128 T=dp[n][x][0]+dp[n][x][1];
        __int128 K=cnt[n][x][0]+cnt[n][x][1];
        if(K) res+=(ld)T/x;
    }
     cout << scientific << setprecision(12) << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
