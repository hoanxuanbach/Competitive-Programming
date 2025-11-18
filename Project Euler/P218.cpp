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
    int N;cin >> N;

    int S=sqrtl(N);

    int cnt=0;
    for(int x=1;x*x<=S;x++){
        for(int y=1;y<x;y++){
            if((x&1)==(y&1)) continue;
            if(__gcd(x,y)!=1) continue;
            
            int n=x*x-y*y,m=2*x*y,d=x*x+y*y;
            if(d>S) continue;
            if(m<n) swap(m,n);
            int c=d*d;
            int a=m*m-n*n;
            int b=2*m*n;
            cout << a << ' ' << b << ' ' << c << '\n';
            a%=168;
            b%=168;
            if((a*b)%168!=0){
                cnt++;
            }
        }
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
