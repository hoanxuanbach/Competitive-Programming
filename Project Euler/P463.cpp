#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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
    int N=1;
    for(int i=0;i<37;i++) N*=3;

    map<int,int> mp;
    function<int(int)> S = [&](int n){
        if(n<=2) return n;
        else if(n==3) return 5LL;
        if(mp.find(n)!=mp.end()) return mp[n];
        
        int res=S(n/2)+4;
        
        int X=(n-1)/4;
        res=(res+2*(S(2*X+1)-S(X)-1)+mod)%mod;
        res=(res-S(X)+mod)%mod;


        X=(n-3)/4;
        res=(res+3*(S(2*X+1)-S(X)-1)+mod)%mod;
        res=(res-2*S(X)+mod)%mod;

        return mp[n]=res;
    };
    cout << (S(N)+mod)%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
