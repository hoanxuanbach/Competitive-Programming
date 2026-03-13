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
void solve(){
    int k,n;cin >> n >> k;
    ld T=1,res=0;
    for(int i=1;i<=k;i++) T*=(ld)(n-i+1)/n;
    res+=T;
    for(int x=1;2*x<=k;x++){
        T/=2;T/=x;T/=(n-k+x);
        T*=(k-2*x+1);T*=(k-2*x+2);
        res+=T;
    }
    res=1-res;
    cout << setprecision(10) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
