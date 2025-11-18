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

void solve(){
    int n;cin >> n;
    int s=sqrtl(n);

    auto cal = [&](int x){
        int val = ((__int128)x*(x+1)/2)%mod;
        val = (__int128)val*(2*x+1)%mod;
        val = (val*((2*mod+1)/3))%mod;
        return val;
    };

    int res=0;
    for(int i=1;i<s;i++){
        int r=n/i,l=n/(i+1);
        int val=(cal(r)-cal(l)+mod)%mod;
        res=(res+val*i)%mod;
    }
    for(int i=1;i<=n/s;i++) res=(res+(__int128)i*i%mod*(n/i))%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
