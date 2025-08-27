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

void solve(){
    auto fac = [&](int n){
        int res=1;
        for(int i=1;i<=n;i++) res=res*i%mod;
        return res;
    };
    int n,k;cin >> n >> k;
    cout << fac(k)*fac(n-k)%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}