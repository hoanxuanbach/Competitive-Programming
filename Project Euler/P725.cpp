#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e16;
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
    int N;cin >> N;
    
    int S=10,T=20,res=0;
    vector<vector<int>> dp(S,vector<int>(T,0)),cnt(S,vector<int>(T,0));
    for(int i=1;i<S;i++) dp[i][i]=i,cnt[i][i]=1;
    for(int i=2;i<=N;i++){
        vector<vector<int>> ndp(S,vector<int>(T,0)),ncnt(S,vector<int>(T,0));
        for(int j=0;j<S;j++) for(int k=0;k<T;k++){
            for(int x=0;x<S;x++){
                int nj=max(x,j);
                int nk=min(k+x,T-1);
                (ndp[nj][nk]+=dp[j][k]*10+cnt[j][k]*x)%=mod;
                (ncnt[nj][nk]+=cnt[j][k])%=mod;
            }
        }
        swap(dp,ndp);
        swap(cnt,ncnt);
        for(int j=1;j<S;j++) res=(res+dp[j][2*j])%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
