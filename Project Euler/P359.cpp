#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e8;
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

int cal(int n,int m){
    int S=((__int128)n*n/2)%mod,T=n%mod;
    if(!(n&1)) T++;
    if(n==1) m++;

    m--;
    if(m&1) S=(T*T-S+mod)%mod,T++,m--;
    S=(S+((__int128)(2*T+m-1)*m/2)%mod)%mod;
    
    return S;
}

void solve(){
    int X;cin >> X;
    int res=0;
    for(int x=1;x*x<=X;x++){
        if(X%x==0){
            res+=cal(x,X/x);
            if(x*x!=X) res+=cal(X/x,x);
            res%=mod;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
