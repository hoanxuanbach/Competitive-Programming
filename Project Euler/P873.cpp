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

void solve(){
    int A,B,C;cin >> A >> B >> C;

    int N=A+B+C;
    vector<int> fac(N+1,1),dfac(N+1);
    for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i%mod;
    dfac[N]=power(fac[N],mod-2);
    for(int i=N;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    auto cc = [&](int n,int k){
        if(n<k || k<0 || n<0) return 0LL;
        return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
    };
    auto cal = [&](int a,int b){
        int val=cc(A-1,a-1)*cc(B-1,b-1)%mod;
        int cnt=C-2*(a+b-1),d=A+B+1;
        if(cnt<0) return 0LL;
        val=val*cc(cnt+d-1,d-1)%mod;
        return val;
    };
    int res=0;
    for(int x=1;x<=A;x++){
        if(x>1) res+=cal(x,x-1);
        res+=2*cal(x,x);
        if(x<B) res+=cal(x,x+1);
        res%=mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
