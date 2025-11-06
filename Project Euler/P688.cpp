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
const int inv2 = (mod+1)/2;
void solve(){
    int n,res=0;cin >> n;
    for(int k=1;k*(k+1)/2<=n;k++){
        int x=(n+1-k*(k+1)/2);
        int d=(x/k)%mod;
        x%=mod;
        res=(res+x*(d+1)%mod-k*d%mod*(d+1)%mod*inv2%mod+mod)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
