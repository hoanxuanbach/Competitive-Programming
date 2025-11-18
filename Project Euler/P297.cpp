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
    map<int,int> mp;

    function<int(int)> get = [&](int X){
        if(X<=1) return X-1;
        if(mp.find(X)!=mp.end()) return mp[X];
        int A=0,B=1;
        while(B<X) swap(A,B),B+=A;
        return mp[X]=get(A)+(X-A)+get(X-A);
    };
    
    int n;cin >> n;
    cout << get(n) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
