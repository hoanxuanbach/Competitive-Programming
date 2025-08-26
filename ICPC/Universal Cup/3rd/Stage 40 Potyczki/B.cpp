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

void solve(){
    function<int(int,int,int,int)> f = [&](int l,int x,int d,int k){
        if(k==0) return ((2*l+d*(x-1))%mod)*(x%mod)%mod*((mod+1)/2)%mod;
        if(d&1) return (f(l,(x+1)>>1,d<<1,k)+f(l+d,(x>>1),d<<1,k))%mod;
        if(l&1) return f(3*l+1,x,3*d,k-1);
        else return f(l>>1,x,d>>1,k-1);
    };
    int N,k;cin >> N >> k;
    cout << f(1,N,1,k) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
