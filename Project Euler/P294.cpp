#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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

int h[25][25];
int dp[25][25][25];

void solve(){

    int n=1;
    for(int i=0;i<12;i++) n*=11;

    //int n;cin >> n;

    int M=23;
    vector<int> f(M-1);f[0]=1;
    for(int i=1;i<M-1;i++) f[i]=f[i-1]*10%M;
    
    h[0][0]=1;
    for(int i=1;i<=M;i++) for(int j=1;j<=i;j++) for(int d=1;d<=min(i,9LL);d++) h[i][j]=(h[i][j]+h[i-d][j-1])%mod;

    auto C = [&](int m,int k){
        if(k>m) return 0LL;
        
        int val=1;
        __int128 d=1;
        for(int i=1;i<=k;i++) d*=i;
        for(int i=0;i<k;i++){
            int g=__gcd(d,(__int128)(m-i));d/=g;
            val=((m-i)/g)%mod*val%mod;
        }
        cout << m << ' ' << k << ' ' << val << '\n';

        return val;
    };

    auto g = [&](int m,int k){
        int cnt=0;
        for(int i=1;i<=min(m,k);i++) cnt=(cnt+h[k][i]*C(m,i))%mod;
        return cnt;
    };

    cout << n << '\n';

    vector<int> d(M);
    for(int i=1;i<M;i++) d[i]+=n/(M-1);
    for(int i=0;i<n%(M-1);i++) d[f[i]]++;

    dp[0][0][0]=1;
    for(int i=0;i<M-1;i++){
        vector<int> cnt(M+1);
        for(int s=0;s<=M;s++) cnt[s]=g(d[i+1],s);
        cnt[0]=1;
        for(int j=0;j<M;j++) for(int k=0;k<=M;k++){
            for(int s=0;s<=M-k;s++) (dp[i+1][(j+s*(i+1))%M][k+s]+=dp[i][j][k]*cnt[s])%=mod;
        }
    }
    cout << dp[M-1][0][M] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
