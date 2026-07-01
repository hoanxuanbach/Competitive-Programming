#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 982451653;
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

    int res=1;
    
    int S=sqrtl(2*N)+10;
    vector<int> A(S+1,1),B(S+1,1),inv(S+1,1),T(S+1,0);
    for(int i=2;i<=S;i++) A[i]=A[i-1]*i%mod;
    B[S]=power(A[S],mod-2);
    for(int i=S;i>=1;i--) B[i-1]=B[i]*i%mod,inv[i]=B[i]*A[i-1]%mod;
    for(int i=2;i<=S;i++) T[i]=(T[i-1]+A[i]*(i-2))%mod;

    auto get = [&](int l,int r){
        if(l>r) return 0LL;
        return (T[r]-T[l-1]+mod)*B[l-1]%mod;
    };

    int cnt=1;
    for(int i=3;i<=S;i++){
        int d=(i+3)*(i-2)/2;
        if(d>N) break;
        if(d<=N) res=(res+A[i]*inv[2]%mod*(i-2))%mod,cnt++;
        if(d<N) res=(res+A[i]*inv[2]%mod*inv[i]%mod*(i+1)%mod*(i-2))%mod,cnt++;
    }

    int R=S;
    for(int i=S;i>=2;i--){
        int d=(i+2)*(i-1)/2;
        if(d>N) continue;
        int mul=A[i];
        while(R>=i+2 && d+(R-i-1)*(R+i+2)/2>N) R--;
        cnt+=(R-i);
        res=(res+mul*(i-1+get(i+2,R)))%mod;
    }
    cout << cnt << '\n';
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
