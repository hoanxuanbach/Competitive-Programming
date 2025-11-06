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
    int res=0;
    for(int y=0;163*y*y<=4*N;y++){
        int k=(1+(y!=0));
        int m=4*N-163*y*y;
        m=sqrtl(m);
        int l=-m-y,r=m-y;
        if(abs(l)&1) l++;
        if(abs(r)&1) r--;
        int cnt=(r-l)/2+1;
        res+=cnt*k;
    }
    cout << res-1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
