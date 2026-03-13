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
    int N;cin >> N;

    int S=sqrtl(N)+1;
    vector<int> f(S,-1),g(S,-1);
    function<int(int)> cal = [&](int x){
        int n=N/x;
        if(x<S){
            if(f[x]!=-1) return f[x];
        }
        else if(g[n]!=-1) return g[n];

        int cnt=n;
        for(int i=2;i<=min(n,20LL);i++) cnt=min(cnt,cal(x*i)+i+2+n%i);

        if(x<S) return f[x]=cnt;
        else return g[n]=cnt;
    };
    cout << cal(1) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}