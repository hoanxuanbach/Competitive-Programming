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
    /*
    S(m,n) = ((m+2)*(m+1)/2)^n-(m+1)^n
    E(m,n) = v2((m+1)^n * ((m+2)^n - 2^n))  - n
    = v2(m+1)*n+v2((m+2)^n-2^n)-n
    m even -> E(m,n) = v2(k^n-1), k = m/2+1
    m odd ->  E(m,n) = v2(m+1)*n-n 
    
    v2(k^n-1)
    k even -> v2(k^n-1) = 0
    n = 2^x*d
    -> v2(k^n-1) = v2(k^(2^x)-1)
    */

    auto v2 = [&](int x){
        int d=0;
        while(x%2==0) x/=2,d++;
        return d;
    };
    auto f = [&](int n){
        return n-__builtin_popcountll(n);
    };

    int n=904961;
    int M;cin >> M;
    int A=M/2,B=(M+1)/2;
    cout << f(B)*n+f(A) << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
