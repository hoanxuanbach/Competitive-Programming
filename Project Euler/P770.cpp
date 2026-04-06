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
#define ld long double 

void solve(){
    ld S;cin >> S;S=1/S-0.5;

    ld X=0.5;
    for(int N=1;N<=1000000000;N++){
        X=X*(2*N-1)/(2*N);
        if(N%100000==0) cout << N << ' ' << setprecision(10) << fixed << X << endl;
        if(X<=S){
            cout << N << endl;
            return;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
