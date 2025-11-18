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
    map<pii,int> mp;
    for(int i=0;i<N;i++) for(int j=1;j<N;j++){
        if(i*i+j*j>=N*N) continue;
        int g=__gcd(i,j);
        mp[{i/g,j/g}]++;
    }
    int A=0,B=0,C=0;
    for(auto [x,d]:mp) A+=d,B+=d*d,C+=d*d*d;
    int res=(8*A*A*A-12*A*B+4*C)/3;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
