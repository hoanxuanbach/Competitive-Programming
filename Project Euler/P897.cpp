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

ld cross(pair<ld,ld> A,pair<ld,ld> B){
    return A.first*B.second-A.second*B.first;
}

void solve(){
    int N,K;cin >> N >> K;
    ld delta=(ld)2/N;
    vector<pair<ld,ld>> P(N+1);
    for(int i=0;i<=N;i++){
        ld x=-1+delta*i;
        P[i]={x,x*x*x*x};
    }
    vector<vector<ld>> dp(N+1,vector<ld>(K+1,-inf));
    dp[0][0]=0;
    for(int i=1;i<=N;i++) for(int j=1;j<=min(K,i);j++){
        int l=j-1,r=i-1;
        auto eval = [&](int x){
            ld val=dp[x][j-1]+cross(P[x],P[i]);
            dp[i][j]=max(dp[i][j],val);
            return val;
        };
        while(l<=r){
            int x=l+(r-l)/3,y=r-(r-l)/3;
            if(eval(x)<eval(y)) l=x+1;
            else r=y-1;
        }
    }
    cout << setprecision(9) << fixed << (dp[N][K]+cross(P[N],P[0]))/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
