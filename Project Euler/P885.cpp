#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1123455689;
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
    int N;cin >> N;
    vector<int> pw(N,1);
    for(int i=1;i<N;i++) pw[i]=pw[i-1]*10%mod;
    vector<int> fac(N+1,1);
    for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i;

    int S=0;
    for(int l=0;l<N;l++) for(int r=l;r<N;r++) for(int k=1;k<=9;k++){
        int x=N-r-1,A=0;
        for(int i=l;i<=r;i++) A=(A+pw[i])%mod;
        A=(A*k)%mod;
        A=(fac[N]/fac[l]/fac[r-l+1]/fac[x])%mod*A%mod;
        A=A*power(k,x)%mod*power(9-k,l)%mod;
        S=(S+A)%mod;
    }
    cout << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
