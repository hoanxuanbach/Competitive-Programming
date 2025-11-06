#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int mod = 1e9+7;
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int P=8,Q=52;
    int S=power(3,P,mod);
    vector<int> f(3*S+1);f[0]=1;
    for(int i=0;i<S;i++){
        for(int i=3*S;i>=0;i--) if(f[i]){
            f[i+1]^=1;f[i+3]^=1;
        }
    }
    int res=0;
    for(int i=0;i<=3*S;i++) if(f[i]){
        int k=i*power(2,Q,mod-1)%(mod-1);
        res=(res+power(2,k,mod))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
