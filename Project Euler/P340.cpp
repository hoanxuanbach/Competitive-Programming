#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
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
    int A,B,C;//cin >> A >> B >> C;
    A=power(21,7);
    B=power(7,21);
    C=power(12,7);
    //cout << ' ' << A << ' ' << B << ' ' << C << ' ' << B/A << '\n';
    /*
    int res=0;
    for(int n=0;n<=B;n++){
        int d=(B-n)/A+1;
        res+=n+3*d*(A-C)+d*A-C;
    }
    cout << res << '\n';
    */

    int b=B%mod,k=(4*A-3*C)%mod;
    int res=(b*(b+1)/2-(b+1)*C)%mod;

    int s=B/A,d=B-A*s;
    s%=mod;d%=mod;
    int T=(d+1)*(s+1)%mod;
    T=(T+(s*(s+1)/2)%mod*A)%mod;
    res=(res+T*k)%mod;
    cout << res << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
