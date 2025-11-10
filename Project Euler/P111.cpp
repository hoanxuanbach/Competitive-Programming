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
    int res=0;
    function<bool(int,int,int,int)> dfs = [&](int x,int n,int k,int d){
        if(k>n) return false;
        if(!n){
            for(int i=2;i*i<=x;i++) if(x%i==0) return false;
            res+=x;
            return true;
        }
        bool ok=false;
        for(int a=0;a<=9;a++) if(dfs(x*10+a,n-1,k-(a==d),d)) ok=true;
        return ok;
    };
    auto check = [&](int n,int k,int d){
        bool ok=false;
        for(int i=1;i<=9;i++) if(dfs(i,n-1,k-(d==i),d)) ok=true;
        return ok;
    };
    auto cal = [&](int n,int d){
        int k=n;
        while(k>0 && !check(n,k,d)) k--;
        return k;
    };
    int N;cin >> N;
    for(int d=0;d<=9;d++){
        cout << cal(N,d) << '\n';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
