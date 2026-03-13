#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int mod=1;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(__int128)res*a%mod;
        a=(__int128)a*a%mod;n>>=1;
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
    int n,p,k;cin >> n >> p >> k;
    for(int i=0;i<k;i++) mod*=p;

    vector<int> T(n+1);
    T[0]=290797;
    for(int i=1;i<=n;i++) T[i]=T[i-1]*T[i-1]%50515093;
    for(int i=0;i<=n;i++) T[i]%=p;


    int res=0,mul=power(p-1,mod/p*(p-1)-1),dd=1;

    cout << mod << '\n';

    for(int i=1;i<=n;i++){
        dd=(__int128)dd*p%mod;
        int nd=(__int128)(dd+mod-1)*mul%mod;
        res=(res+(__int128)T[i]*nd%mod)%mod;
        /*
        (p^i-1)/(p-1)
        */

    }
    cout << res << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
