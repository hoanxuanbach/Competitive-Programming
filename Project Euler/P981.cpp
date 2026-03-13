#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 888888883;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn];
int C(int n,int k){
    if(n==k) return 1;
    if(n<0 || k<0 || n<k) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int f[105][105][105][2];

void solve(){
    int N;cin >> N;

    int S=2*N*N*N;
    fac[0]=1;
    for(int i=1;i<=S;i++) fac[i]=fac[i-1]*i%mod;
    dfac[S]=power(fac[S],mod-2);
    for(int i=S;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;


    int res = 0;
    auto g = [&](int a,int b,int x){
        pair<int,int> P={0,0};
        for(int i=0;i<=x;i++){
            int cnt=C(i+b-1,b-1)*C(x-i+a-1,a-1)%mod;
            if(i&1) P.second=(P.second+cnt)%mod;
            else P.first=(P.first+cnt)%mod;
        }
        return P;
    };
    for(int k=0;k<=1;k++) for(int x=k;x<N;x+=2) for(int y=k;y<N;y+=2) for(int z=k;z<N;z+=2){
        cout << x << ' ' << y << ' ' << z << endl;
        int X=x*x*x,Y=y*y*y,Z=z*z*z;

        int A=1,B=0;

        int a=X/2+1,b=X+1-a;
        auto [dA,dB]=g(a,b,Y);
        int nA=(A*dA+B*dB)%mod,nB=(A*dB+B*dA)%mod;
        A=nA;B=nB;

        a=(X+Y)/2+1,b=(X+Y+1)-a;
        tie(dA,dB)=g(a,b,Z);
        nA=(A*dA+B*dB)%mod,nB=(A*dB+B*dA)%mod;
        A=nA;B=nB;

        if(((X+Y+Z+1)/2)&1) res=(res+B)%mod;
        else res=(res+A)%mod;
    }

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
