#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 100000;
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
    for(int a=1;a<=N;a*=2) for(int b=a;b<=N;b*=5){
        int n=N/b;
        for(int x=0;x<mod;x++){
            if(x%2==0 || x%5==0) continue;
            if(x<=n){
                int d=(n-x)/mod+1;
                res=res*power(x,d)%mod;
            }
        }
    }
    int f2=0,f5=0;
    
    int X=N;
    while(X){
        X/=2;
        f2+=X;
    }
    X=N;
    while(X){
        X/=5;
        f5+=X;
    }
    int k=f2-f5;
    res=res*power(2,k)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
