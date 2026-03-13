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
    

    int T=0;
    function<void(int,int,int)> dfs = [&](int x,int l,int r){
        T+=(r-l+1);
        for(int i=(l+x-1)/x;x*(i-1)+1<=r;i++){
            int lt=max(l,(i-1)*x+1),rt=min(r,i*x);
            int nx=(x+i)/2;
            if(nx!=x) dfs(nx,lt,rt);
        }
    };
    
    int l=1,r=1;
    for(int i=1;i<=13;i++) l*=10;
    r=l*10-1;
    
    dfs(7000000,l,r);
    long double res=(long double)T/(r-l+1);
    cout << setprecision(10) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
