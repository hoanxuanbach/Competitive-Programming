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
    int N;cin >> N;
    auto f = [&](int k,ld a){
        auto g = [&](ld S){
            ld ret=S/2*sqrtl(a*a-S*S)+a*a/2*asin(S/a)-S;
            return ret;
        };  
        ld S=a*a-1;
        if(S<0) return (ld)0;
        S=sqrtl(S);
        if(S<1) return (ld)0;
        ld res=g(S)-g(1);
        return res/k;
    };

    ld res=0;
    for(int k=1;k<=N;k++){
        res+=f(k,k+(ld)1/2);
        res-=f(k,k-(ld)1/2);
    }    
    cout << setprecision(5) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
