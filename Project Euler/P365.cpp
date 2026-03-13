#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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
    int L,R;cin >> L >> R;
    vector<int> f(R),X;
    for(int i=2;i<R;i++) if(!f[i]){
        if(i>L) X.push_back(i);
        for(int j=i;j<R;j+=i) f[j]=1;
    }
    int n=(int)X.size();
    vector<int> d(n);
    for(int t=0;t<n;t++){
        int x=X[t];

        vector<int> fac(x,1),dfac(x,1);
        for(int i=1;i<x;i++) fac[i]=fac[i-1]*i%x;
        dfac[x-1]=power(fac[x-1],x-2,x);
        for(int i=x-1;i>=1;i--) dfac[i-1]=dfac[i]*i%x;

        auto C = [&](int N,int K){
            if(N<0 || K<0 || N<K) return 0LL;
            return fac[N]*dfac[K]%x*dfac[N-K]%x;
        };

        d[t]=1;
        int A=1e18,B=1e9;
        while(A || B){
            int da=A%x,db=B%x;A/=x;B/=x;
            d[t]=d[t]*C(da,db)%x;
        }
    }
    int res=0;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) for(int k=j+1;k<n;k++){
        int x=X[i],y=X[j],z=X[k];
        int dx=d[i],dy=d[j],dz=d[k];
        int mod=x*y*z;
        int val=dx*y*z*power(y*z%x,x-2,x)+dy*x*z*power(x*z%y,y-2,y)+dz*x*y*power(x*y%z,z-2,z);
        val%=mod;
        res+=val;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
