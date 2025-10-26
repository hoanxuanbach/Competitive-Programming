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
    int N=10000000,M=1000;

    vector<int> f(N);
    function<int(int)> g = [&](int i){
        if(i==1 || i==89) return f[i]=i;
        if(f[i]) return f[i];
        int d=i,x=0;
        while(d){
            int k=d%10;
            d/=10;x+=k*k;
        }
        return f[i]=g(x);
    };

    int cnt=0;
    for(int i=1;i<M;i++) cnt+=(g(i)==89);
    for(int i=M;i<N;i++){
        int d=i,x=0;
        while(d){
            int k=d%10;
            d/=10;x+=k*k;
        }
        f[i]=f[x];
        cnt+=(f[i]==89);
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
