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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int f[100000005];

void solve(){
    int N;cin >> N;
    for(int x=1;x*x<=N;x++) for(int y=x;x*x+y*y<=N;y++){
        int T=x*x+y*y,k=T%20;T/=20;
        f[T]|=(1LL<<(3*k));
    }
    for(int x=1;x*x<=N;x++) for(int y=1;x*x+2*y*y<=N;y++){
        int T=x*x+2*y*y,k=T%20;T/=20;
        f[T]|=(1LL<<(3*k+1));
    }
    for(int x=1;x*x<=N;x++) for(int y=1;x*x+3*y*y<=N;y++){
        int T=x*x+3*y*y,k=T%20;T/=20;
        f[T]|=(1LL<<(3*k+2));
    } 
    int cnt=0;
    for(int x=1;x*x<=N;x++) for(int y=1;x*x+7*y*y<=N;y++){
        int T=x*x+7*y*y,k=T%20;T/=20;
        if(((f[T]>>(3*k))&7)==7){
            cnt++;
            f[T]^=7LL<<(3*k);
        }
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
