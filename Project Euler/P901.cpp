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
    auto eval = [&](ld d){
        ld a=0,b=d,T=b+exp(-a)+exp(-b);
        for(int i=0;i<300;i++){
            if(isinf(b)) break;
            ld c=exp(b-a);
            if(c<b) return (ld)inf;
            T+=exp(-c);
            a=b;b=c;
        }
        return T;
    };
    ld l=0,r=1;
    for(int iter=0;iter<10000;iter++){
        ld x=l+(r-l)/3,y=r-(r-l)/3;
        double fx=eval(x),fy=eval(y);
        if(fx<fy) r=y;
        else l=x;
    }
    cout << setprecision(9) << fixed << (l+r)/2 << '\n';
    cout << setprecision(9) << fixed << eval((l+r)/2) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
