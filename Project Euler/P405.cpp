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
const int mod = 410338673;
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int inv2=(mod+1)/2;
const int inv3=(mod+1)/3;
const int inv5=(3*mod+1)/5;

void solve(){
    int K;cin >> K;
    int P=mod/17*16;
    int N=power(10,K,P);
    int X=3*(power(4,N,mod)-1);
    int Y=(power(4,N,mod)-1)*inv5%mod;
    int Z=(power(2,2*N+2,mod)-power(2,N+2,mod)+mod)%mod;
    int res=(Y+Z+mod-X)*inv3%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
