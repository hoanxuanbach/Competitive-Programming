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

int dp[20][2][2][2];

void solve(){
    int N;cin >> N;
    for(int i=1;i<=N;i++){
        for(int x=1;x<=15;x++){
            int a=0,b=(x==1),c=(x==10);
            dp[i][a][b][c]++;
        }
        for(int a=0;a<=1;a++) for(int b=0;b<=1;b++) for(int c=0;c<=1;c++){
            for(int x=0;x<=15;x++){
                int na=a|(x==0),nb=b|(x==1),nc=c|(x==10);
                dp[i][na][nb][nc]+=dp[i-1][a][b][c];
            }
        }
    }
    int res=dp[N][1][1][1];
    cout << res << '\n';
    string S;
    while(res){
        int x=res%16;res/=16;
        if(x<=9) S+=char('0'+x);
        else S+=char('A'+x-10);
    }
    reverse(S.begin(),S.end());
    cout << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
