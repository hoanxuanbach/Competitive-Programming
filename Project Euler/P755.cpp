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

    vector<int> S,X;
    X={0,1,2};
    S={0,1,3};
    while(X.end()[-2]+X.back()<=N){
        X.push_back(X.end()[-2]+X.back());
        S.push_back(S.back()+X.back());
    }   
    function<int(int,int)> f = [&](int n,int i){
        if(n==0) return 1LL;
        if(n<X[i]) return f(n,i-1);
        if(n>=S[i]) return (1LL<<i);
        return f(n-X[i],i-1)+f(n,i-1);
    };

    cout << f(N,(int)X.size()-1) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
