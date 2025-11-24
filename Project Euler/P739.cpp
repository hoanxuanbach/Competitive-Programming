#include<bits/stdc++.h>
using namespace std;

int fac[200000005],dfac[200000005];

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

    fac[0]=1;
    for(int i=1;i<2*n;i++) fac[i]=1LL*fac[i-1]*i%mod;
    dfac[2*n-1]=power(fac[2*n-1],mod-2);
    for(int i=2*n-1;i>=1;i--) dfac[i-1]=1LL*dfac[i]*i%mod;

    auto C = [&](int N,int K){
        if(N<K || K<0 || N<0) return 0LL;
        return 1LL*fac[N]*dfac[K]%mod*dfac[N-K]%mod;
    };

    n--;
    int res=0;
    int A=2,B=1;
    for(int i=n;i>=0;i--){
        int cnt=(C(n+i,n)-C(n+i,n+1)+mod)%mod;
        //cout << '*' << cnt << '\n';
        if(i<n){
            cnt=cnt*(B-A+mod)%mod;
            //cout << B-A << '\n';
        }
        //else cout << 1 << '\n';
        res=(res+cnt)%mod;
        swap(A,B);B=(B+A)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
