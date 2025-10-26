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
    int n;cin >> n;
    string res(n,'N');
    vector<array<int,3>> X(n);
    for(int i=0;i<n;i++){
        cin >> X[i][0] >> X[i][1];
        X[i][2]=i;
    }
    sort(X.begin(),X.end());
    for(int i=0;i+1<n;i+=2){
        auto [a,b,x]=X[i];
        auto [c,d,y]=X[i+1];
        if(b<=d) res[y]='T';
        else res[x]='T';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
