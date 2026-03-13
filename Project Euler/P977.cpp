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
    int n;cin >> n;
    int res=0;
    for(int d=1;d<=n;d++){
        int x=n/d,s=n%d;
        (res+=power(x+1,s)*power(x,d-s)%mod)%=mod;

        /*
        for(int k=d;k<n;k++){
            int m=k/d,t=k%d;
            (res+=power(m+1,t)*power(m,d-t)%mod*(m-(t==0)))%=mod;
        }
        */

        for(int m=1;m*d<n;m++){
            int t=min(n-m*d,d);
            (res+=power(m,d)*(m-1))%=mod;
            int cur=power(m,d)*m%mod,dd=(m+1)*power(m,mod-2)%mod;
            int mul=(power(dd,t)+mod-dd)*power(dd-1,mod-2)%mod;
            res=(res+cur*mul)%mod;
        }
        
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
