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
    vector<int> X;

    int N=1e7;
    for(int a=1;a<=N;a++){
        for(int u=1;u<=N*N;u*=11){
            int d=4*u+5*a*a;
            int s=sqrtl(d);
            if(s*s!=d) continue;
            int b=(s+a);
            if(b%2!=0) continue;
            b/=2;
            if((a*(3*a+b))%u!=0) continue;
            int c=(a*(3*a+b))/u;
            X.push_back(c);
        }
    }
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
    int T=0;
    for(int i=0;i<30;i++) T+=X[i];
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
