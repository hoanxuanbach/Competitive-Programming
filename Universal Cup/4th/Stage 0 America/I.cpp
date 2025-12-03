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

#define ld long double
void solve(){
    int n;cin >> n;
    vector<ld> X(n+1),Y(n+1);
    for(int i=0;i<n;i++) cin >> X[i] >> Y[i];

    vector<int> ans;
    X[n]=X[0];Y[n]=Y[0];
    for(int i=0;i<n;i++){
        for(int t=0;t<=1;t++){
            for(int x=-500;x<=500;x++) if(X[i]<x && x<X[i+1]){
                ld y=(Y[i+1]-Y[i])/(X[i+1]-X[i])*(x-X[i])+Y[i];
                ans.push_back(floor(y));
            }
            swap(X[i],Y[i]),swap(X[i+1],Y[i+1]);
        }
    }
    cout << (int)ans.size() << '\n';
    for(int x:ans) cout << x << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
