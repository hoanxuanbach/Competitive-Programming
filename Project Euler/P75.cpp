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
    int N;cin >> N;
    vector<int> cnt(N+1);
    for(int m=2;m<=N;m++) for(int n=1;n<m && 2*m*(n+m)<=N;n++){
        if((n&1) && (m&1)) continue;
        int g=__gcd(n,m);
        if(g==1){
            //cout << m*m-n*n << ' ' << m*m+n*n << ' ' << 2*n*m << '\n';
            cnt[2*m*(n+m)]++;
        }
    }
    int res=0;
    for(int i=N;i>=1;i--){
        for(int j=i*2;j<=N;j+=i) cnt[j]+=cnt[i];
    }
    for(int i=1;i<=N;i++) res+=(cnt[i]==1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
