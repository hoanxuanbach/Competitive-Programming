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
    
    int x=0;
    vector<int> A(n+1),B(n+1);
    for(int i=1;i<n;i++){
        char c;cin >> c;
        if(c=='1') A[i-x]++,x=i;
    }
    A[n-x]++;
    
    x=0;
    for(int i=1;i<n;i++){
        char c;cin >> c;
        if(c=='1') B[i-x]++,x=i;
    }
    B[n-x]++;

    vector<int> a,b;
    for(int i=1;i<=n;i++) if(A[i]&1) a.push_back(i);
    for(int i=1;i<=n;i++) if(B[i]&1) b.push_back(i);

    int res=0;
    for(int x:a) for(int y:b) res^=(x*y);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}