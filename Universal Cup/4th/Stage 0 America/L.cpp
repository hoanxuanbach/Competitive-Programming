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
    int r,w,h;cin >> r >> w >> h;
    if(w<h) swap(h,w);
    int d=sqrtl(2)*r/w,res=0;
    for(int k=-300;k<=300;k++){
        int a=d+k;
        if(a<0 || a*w>2*r) continue;
        int b=sqrtl(4*r*r-a*a*w*w)/h;
        res=max(res,a*b);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
