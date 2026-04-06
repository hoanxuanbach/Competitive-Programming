#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

    function<int(int)> f = [&](int N){
        if(N<=0) return 0LL;
        int T=1;
        while(T*4<=N) T*=4;
        int res=(__int128)T*(T-1)/2*3%mod;N-=T;
        res+=(__int128)T*N*6%mod;
        while(N>=T) res+=(__int128)T*(T-1)/2*3%mod,N-=T;
        return res+f(N);
    };

    int N;cin >> N;
    int res=0,T=1;
    while((T*4-1)/3<=N) T*=4;
    res+=(__int128)T*(T-1)/2%mod;N-=(T-1)/3;
    res+=(__int128)T*N*6%mod+f(N);
    cout << res%mod << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
