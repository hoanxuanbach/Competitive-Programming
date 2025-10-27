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
    int k,n;cin >> k >> n;n/=k;
    
    int X=power(2,n);
    vector<int> fac(k+1,1);
    for(int i=1;i<=k;i++) fac[i]=fac[i-1]*i%mod;
    vector<int> dfac(k+1,1);
    dfac[k]=power(fac[k],mod-2);
    for(int i=k;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
    
    int res=0,cur=((k&1)?X:1);
    for(int x=(k&1);x<=k;x+=2){
        int y=(k-x)/2;
        int mul=fac[k]*dfac[x]%mod*dfac[y]%mod*dfac[y]%mod;
        res=(res+cur*mul)%mod;
        cur=cur*X%mod*X%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
