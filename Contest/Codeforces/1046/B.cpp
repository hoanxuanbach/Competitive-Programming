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
    int X=1e9;

    int n,A=-2*X,B=2*X;cin >> n;
    for(int i=0;i<n;i++){
        int x,y;cin >> x >> y;
        A=max(A,x+y);
        B=min(B,x-y);
    }
    auto f = [&](char c,int x){
        cout << "? " << c << ' ' << x << endl;
        int val;cin >> val;
        return val;
    };
    f('R',X);f('R',X);f('U',X);
    int S=f('U',X)-4*X+A;
    f('L',X);f('L',X);f('L',X);
    int T=f('L',X)-4*X-B;
    cout << "! " << (S-T)/2 << ' ' << (S+T)/2 << endl;

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
