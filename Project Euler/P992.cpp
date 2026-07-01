#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 987898789;
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

int f[505][10505][2];
int F(int N,int K){
    memset(f,0,sizeof(f));
    combi(N+K);
    f[0][K-1][1]=1;
    for(int i=1;i<N;i++){
        int d=K+i;
        for(int x=0;x<=d;x++){
            if(x) (f[i][d-x][0]+=(f[i-1][x][0]+f[i-1][x][1])*C(d-1,x-1))%=mod;
            if(x<d) (f[i][d-x-1][1]+=f[i-1][x][1]*C(d-1,x))%=mod;
        }
    }
    int res=0;
    for(int x=0;x<=K+N;x++) res=(res+f[N-1][x][0]+f[N-1][x][1]*2)%mod;
    return res;
};

void solve(){
    int n=500,k=1;
    int res=0;
    for(int s=0;s<=4;s++){
        res=(res+F(n,k))%mod;
        k*=10;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
