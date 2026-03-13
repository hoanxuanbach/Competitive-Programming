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
 
const int maxn = 3e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int inv2=(mod+1)/2;
int fac[maxn],dfac[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0LL;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    string s;cin >> s;
    int n=(int)s.length();
    combi(n);

    int l=0,T=power(2,n)-1;
    for(int i=1;i<n;i++) if(s[i]!=s[l]){
        int k=i-l,d=0;
        for(int j=k;j>=1;j--){
            d=(d*2+C(n-j-1,l-1)+C(n-j-1,l+k-j))%mod;
            T=(T+mod-d)%mod;
        }
        for(int j=1;j<=k;j++){
            if(l) T=(T+C(n-j-1,l-1)*j)%mod;
            T=(T+C(n-j-1,n-i-1)*j)%mod;
        }
        l=i;
    }
    int k=n-l;
    if(l){
        int d=0;
        for(int j=k;j>=1;j--){
            d=(d*2+C(n-j-1,l-1)+C(n-j-1,l+k-j))%mod;
            T=(T+mod-d)%mod;
        }
        for(int j=1;j<=k;j++) T=(T+C(n-j-1,k-j)*j)%mod;
    }
    else T=n;
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}