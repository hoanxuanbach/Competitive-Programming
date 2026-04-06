#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 987654321;
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

map<pii,int> mp;
int P(int n,int k){
    if(n==1) return 1;
    if(!k || (n&1)) return 2*P(n/2,k^1);
    else return 2*P(n/2,k^1)-1;
};

int S(int n,int k){
    if(n<=1) return n;
    if(!(n&1)) return (S(n-1,k)+P(n,k))%mod;
    if(!k) return (1+4*S(n/2,1))%mod;
    else return (1+4*S(n/2,0)-n/2)%mod;
}

void solve(){
    int N;cin >> N;
    cout << (S(N,0)+mod)%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
