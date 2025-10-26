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
    set<int> T;

    int X=100000;
    for(int n=1;n<=X;n++) T.insert(n*(n+1)/2);

    set<int> P;
    for(int n=1;n<=X;n++) if(T.find(n*(3*n-1)/2)!=T.end()) P.insert(n*(3*n-1)/2);

    set<int> H;
    for(int n=1;n<=X;n++) if(P.find(n*(2*n-1))!=P.end()) H.insert(n*(2*n-1));

    for(int x:H) cout << x << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
