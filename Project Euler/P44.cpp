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
    int N=10000;
    
    int d=inf;
    set<int> ss;
    for(int i=1;i<N;i++) ss.insert(i*(3*i-1)/2);
    for(int i=1;i<N;i++) for(int j=i+1;j<N;j++){
        int a=i*(3*i-1)/2,b=j*(3*j-1)/2;
        if(ss.find(a+b)==ss.end()) continue;
        if(ss.find(b-a)==ss.end()) continue;
        d=min(d,b-a);
    }
    cout << d << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
