#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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
    int n;cin >> n;

    int S=33;
    vector<int> p(S+1,1);
    for(int i=1;i<=S;i++) p[i]=p[i-1]*3;

    vector<int> f(S);
    for(int i=1;i<=S;i++){
        int l=n,r=n+S-1;
        while(l<=r && l<=p[i]) l++;
        if(l>r) continue;
        int x=power(10,l-1,p[i]);
        for(int j=l;j<=r;j++){
            x*=10;
            f[j-n]+=x/p[i];
            x=x%p[i];
        }
    }
    for(int i=S-1;i>=0;i--){
        if(i) f[i-1]+=f[i]/10;
        f[i]%=10;
    }
    for(int i=0;i<10;i++) cout << f[i];
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
