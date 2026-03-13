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
const int S = 100000;
const ld eps = 1e-9;    
void solve(){
    
    int n,m;cin >> n >> m;
    ld res=(ld)n/2;
    auto f = [&](int i){
        ld a=(ld)(i-1)/n,b=(ld)(n-i)/n;
        ld x=2*a*a+2*b*b-1;
        return x;
    };

    int i=1;
    for(i=1;i+i<=n;i++){
        
        ld x=f(i);

        ld fx=1;
        int s=m;
        while(s){
            if(s&1) fx*=x;
            x*=x;s>>=1;
        }
        if(fx<eps) break;
        res+=fx;
        if(i%100000==0) cout << i << ' ' << fx << endl;
    }
    if(i+i==n+1){
        ld x=f(i);

        ld fx=1;
        int s=m;
        while(s){
            if(s&1) fx*=x;
            x*=x;s>>=1;
        }
        res+=fx/2;
    }
    cout << setprecision(2) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
