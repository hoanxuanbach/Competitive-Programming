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
    auto cal = [&](int n){
        ld y = (n+1-sqrt(2*n))/(n*n+1);
        ld x = y*n;
        ld L = 1-acos(-1)/4;
        ld angle = asin(1-x);
        ld area = (1-x)*y-(angle-(1-x)*(1-y))/2+x*y/2;
        return area/L;
    };
    int N=1;
    while(cal(N)>0.001) N++;
    cout << N << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
