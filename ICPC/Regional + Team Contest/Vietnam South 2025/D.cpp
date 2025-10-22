#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1e9+7;
const int maxn = 5e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int n,k;cin >> n >> k;
    combi(100);

    vector<pair<int,int>> p;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            int x=0;
            while(n%i==0) n/=i,x++;
            p.push_back({i,x});
        }
    }
    if(n>1) p.push_back({n,1});

    int res=1;
    for(auto [x,d]:p){

        vector<int> f(d+1);f[d]=1;
        for(int i=k;i>=1;i--){
            for(int j=1;j<=d;j++) f[j]=f[j]*inv[j+1]%mod;
            for(int j=d;j>=1;j--) f[j-1]=(f[j-1]+f[j])%mod;
        }

        int cur=0,val=1;
        for(int i=0;i<=d;i++){
            cur=(cur+val*f[i])%mod;
            val=val*x%mod;
        }
        res=(res*cur)%mod;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    int test=1;//cin >> test;
    while(test--) solve();
}