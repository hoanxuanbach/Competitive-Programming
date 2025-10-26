#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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
    int n;cin >> n;
    vector<int> S,T;
    S.push_back(0);
    T.push_back(0);
    for(int i=1;i<=n;i++){
        int sz=(int)S.size();
        S.resize(sz+81);
        T.resize(sz+81);
        for(int i=sz-1;i>=0;i--){
            for(int j=1;j<=9;j++) S[i+j*j]=(S[i+j*j]+S[i]*10+T[i]*j)%mod,T[i+j*j]=(T[i+j*j]+T[i])%mod;
            S[i]*=10;
        }
        for(int i=1;i<=9;i++) T[i*i]=(T[i*i]+1)%mod,S[i*i]=(S[i*i]+i)%mod;
    }
    int res=0;
    for(int i=1;i*i<(int)S.size();i++) res=(res+S[i*i])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
