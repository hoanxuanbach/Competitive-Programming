#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1000000087;
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
    vector<vector<int>> d(n+1);
    for(int i=2;i<=n;i++) if(d[i].empty()){
        for(int j=i;j<=n;j+=i) d[j].push_back(i);
    }

    vector<int> fac(2*n+1),dfac(2*n+1),inv(2*n+1);
    fac[0]=dfac[0]=inv[0]=1;
    for(int i=1;i<=2*n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[2*n]=power(fac[2*n],mod-2);
    for(int i=2*n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod,inv[i]=dfac[i]*fac[i-1]%mod;

    int T=0,res=1;
    vector<int> f(n+1);
    for(int i=2;i<=n;i++){
        int s=i;
        for(int x:d[i]){
            res=res*inv[2*f[x]+1]%mod;
            while(s%x==0) s/=x,f[x]++;
            res=res*(2*f[x]+1)%mod;
        }
        T=(T+res)%mod;
    }

    cout << T << '\n';
}   
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
