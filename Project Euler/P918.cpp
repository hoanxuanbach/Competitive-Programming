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
    function<int(int)> f = [&](int n){
        if(n<=1) return n;
        if(mp.find(n)!=mp.end()) return mp[n];
        int res=1+2*f(n/2);
        int x=(n-1)/2;
        res+=f(x)-3*f(x+1)+3;
        return mp[n]=res;
    };

    int N;cin >> N;
    cout << f(N) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
