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
 
const int maxn = 1e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    if(n<k || n<0 || k<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int n,a,b;cin >> n >> a >> b;a=abs(a-b);
    
    map<int,int> mp;
    function<int(int)> cal = [&](int x){
        if(x==1) return 0LL;
        if(mp.find(x)!=mp.end()) return mp[x];
        int l=x/2,r=x-l;
        return mp[x]=(cal(l)+cal(r)+(C(n-l-1,a-1)+C(n-r-1,a-1))*l%mod*r%mod)%mod;
    };
    cout << cal(n)*fac[n-a-1]%mod*fac[a-1]%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    combi(1000000);
    int test=1;cin >> test;
    while(test--) solve();
}
