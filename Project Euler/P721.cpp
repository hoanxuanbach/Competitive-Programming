#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 999999937;
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
    int res=0;
    int N;cin >> N;
    for(int a=1;a<=N;a++){
        int k=sqrtl(a);
        int ga=k,gb=1;
        if(k*k<a) ga++;
        int fa=1,fb=0;

        int m=a*a;
        while(m){
            if(m&1){
                int na=(fa*ga+fb*gb%mod*a)%mod;
                int nb=(fa*gb+fb*ga)%mod;
                fa=na,fb=nb;
            }
            int na=(ga*ga+gb*gb%mod*a)%mod;
            int nb=2*ga*gb%mod;
            ga=na,gb=nb;m>>=1;
        }
        int val=2*fa%mod;
        if(k*k!=a) val=(val+mod-1)%mod;
        res=(res+val)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
