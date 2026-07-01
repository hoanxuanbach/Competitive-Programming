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
const ld PI = acosl(-1);

void solve(){
    int a,b,c;cin >> a >> b >> c;
    if(a<b) swap(a,b);
    if(a<c) swap(a,c);
    if(b>c) swap(b,c);

    ld res=(ld)c*cos(PI/2 - acos((ld)(a*a+c*c-b*b)/(2*a*c)) - acos((ld)1/a));
    cout << res << '\n';

    ld side = sqrtl(12);
    cout << side << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
