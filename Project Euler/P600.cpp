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

void solve(){
    int N;cin >> N;
    vector<int> f(N);
    for(int i=3;i<N;i+=3) f[i]=1;
    for(int i=3;i<N;i++) f[i]+=f[i-2];
    for(int i=3;i<N;i++) f[i]+=f[i-1];
    int res=0;
    for(int T=3;T<=N;T++) for(int S=T-(T/3);3*S<=T+N;S++){
        int k=max(T-S,0LL);
        int nT=T-3*k;
        res+=(1+(S==T))*f[nT];
    } 
    cout << res/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
