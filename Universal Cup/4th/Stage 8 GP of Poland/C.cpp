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

const int inv2=(mod+1)/2;
void solve(){
    int n;cin >> n;

    int res=n;
    int A=0,B=1;
    vector<int> d(n+1);d[0]=1;

    int mul=1,m=1;
    while(A+B<=n && m<n){
        swap(A,B);B+=A;
        vector<int> c=d;
        mul=mul*(++m)%mod;
        for(int i=1;i<=n;i++) c[i]=(c[i]+c[i-1])%mod;

        int add=0;
        for(int x=1;B*x<=n;x++) add=(add+c[n-B*x]*inv2)%mod;
        for(int i=A;i<=n;i++) c[i]=(c[i]+c[i-A])%mod;
        for(int x=1;B*x+A<=n;x++) add=(add+c[n-B*x-A])%mod;

        res=(res+add*mul)%mod;
        for(int i=A;i<=n;i++) d[i]=(d[i]+d[i-A])%mod;
    }
    int total=0;
    for(int i=1;i<=n;i++) total=(total+power(n,i))%mod;
    res=(total+mod-res)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}