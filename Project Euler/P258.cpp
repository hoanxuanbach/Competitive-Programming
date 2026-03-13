#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 20092010;
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

const int M=2000;
vector<int> mul(vector<int> a,vector<int> b){
    int sz=(int)a.size()+(int)b.size()-1;
    vector<int> c(sz);
    for(int i=0;i<(int)a.size();i++) for(int j=0;j<(int)b.size();j++) c[i+j]=(c[i+j]+a[i]*b[j])%mod;
    if(sz>M){
        for(int i=sz-1;i>=M;i--){
            c[i-M]=(c[i-M]+c[i])%mod;
            c[i-M+1]=(c[i-M+1]+c[i])%mod;
        }
        c.resize(M);
    }
    return c;
}

void solve(){
    int n;cin >> n;
    vector<int> a={0,1},s={1};  
    while(n){
        if(n&1) s=mul(s,a);
        a=mul(a,a);n>>=1;
    }
    int res=0;
    for(int x:s) res=(res+x)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
