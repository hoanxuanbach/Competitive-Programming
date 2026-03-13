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

    int res=0;
    auto f = [&](int a,int b){
        int s=a+b,m=N/s;
        /*
        c = d*s 
        g*s >= d*s 
        */
        for(int d=1;d<m;d++){
            int r=min(m-d,(d*s)/b);
            if(r>d) res+=r-d;
        }
    };  
    function<void(int,int,int,int)> dfs = [&](int a,int b,int c,int d){
        int n=a+c,m=b+d;
        if(2*(n+m)>N) return;
        f(n,m);
        dfs(a,b,n,m);dfs(n,m,c,d);
    };
    dfs(0,1,1,1);
    f(1,1);
    
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
